//  mlx_init_loop.m
// By Ol

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl3.h>
#import <AppKit/NSOpenGLView.h>

#include "mlx_int.h"
#include "mlx_new_window.h"

#include "font.c"


@interface MlxLoopHookObj:NSObject
{
  mlx_ptr_t	*mlx_ptr;
}
- (id) initWithPtr:(void *)mlxptr;
- (void) do_loop_hook;
@end
@implementation MlxLoopHookObj
- (id) initWithPtr:(void *)mlxptr
{
  if (self = [super init])
    mlx_ptr = mlxptr;
  return (self);
}
- (void) do_loop_hook
{
  mlx_win_list_t *win;

  if (mlx_ptr->loop_hook != NULL)
    mlx_ptr->loop_hook(mlx_ptr->loop_hook_data);
  win = mlx_ptr->win_list;
  while (win)
    {
      if (win->nb_flush > 0 && win->nb_flush == win->nb_flush_prev)
	{
	  [(id)win->winid selectGLContext];
	  [(id)win->winid mlx_gl_draw];
	  glFlush();
	  win->nb_flush = 0;
	}
      win->nb_flush_prev = win->nb_flush;
      win = win->next;
    }
  [self performSelector:@selector(do_loop_hook) withObject:nil afterDelay:0.0];
}
@end


void *mlx_init()
{
  mlx_ptr_t	*new_mlx;
  int		bidon;
  int		i;

  if ((new_mlx = malloc(sizeof(*new_mlx))) == NULL)
    return ((void *)0);
  new_mlx->win_list = NULL;
  new_mlx->img_list = NULL;
  new_mlx->loop_hook = NULL;
  new_mlx->loop_hook_data = NULL;

  new_mlx->appid = [NSApplication sharedApplication];

  // super magic trick to detach app from terminal, get menubar & key input events
  for (NSRunningApplication * app in [NSRunningApplication runningApplicationsWithBundleIdentifier:@"com.apple.finder"])
    {
      [app activateWithOptions:NSApplicationActivateIgnoringOtherApps];
      break;
    }
  usleep(100000);
  ProcessSerialNumber psn = { 0, kCurrentProcess };
  (void) TransformProcessType(&psn, kProcessTransformToForegroundApplication);
  usleep(100000);
  [[NSRunningApplication currentApplication] activateWithOptions:NSApplicationActivateIgnoringOtherApps];

  // load font
  new_mlx->font = mlx_new_image(new_mlx, (FONT_WIDTH+2)*95, FONT_HEIGHT);
  i = 0;
  while (i < 4*(FONT_WIDTH+2)*95*FONT_HEIGHT)
    {
      new_mlx->font->buffer[i+0] = font_atlas.pixel_data[i+2];
      new_mlx->font->buffer[i+1] = font_atlas.pixel_data[i+1];
      new_mlx->font->buffer[i+2] = font_atlas.pixel_data[i+0];
      ((unsigned char *)new_mlx->font->buffer)[i+3] = 0xFF-font_atlas.pixel_data[i+3];
      i += 4;
    }

  new_mlx->font->vertexes[2] = FONT_WIDTH;
  new_mlx->font->vertexes[4] = FONT_WIDTH;
  new_mlx->font->vertexes[5] = -FONT_HEIGHT+1;
  new_mlx->font->vertexes[7] = -FONT_HEIGHT+1;

  return ((void *)new_mlx);
}


void mlx_loop(mlx_ptr_t *mlx_ptr)
{
    [NSRunLoop currentRunLoop];
  [[[MlxLoopHookObj alloc] initWithPtr:mlx_ptr] performSelector:@selector(do_loop_hook) withObject:nil afterDelay:0.0];
  [NSApp run];
}


void mlx_pixel_put(mlx_ptr_t *mlx_ptr, mlx_win_list_t *win_ptr, int x, int y, int color)
{
  [(id)(win_ptr->winid) selectGLContext];
  [(id)(win_ptr->winid) pixelPutColor:color X:x Y:y];
  win_ptr->nb_flush ++;
}


int     mlx_do_sync(mlx_ptr_t *mlx_ptr)
{
  mlx_win_list_t *win;

  win = mlx_ptr->win_list;
  while (win)
    {
      [(id)(win->winid) selectGLContext];
      [(id)(win->winid) mlx_gl_draw];
      glFlush();
      win = win->next;
    }
  return (0);
}


int mlx_loop_hook(mlx_ptr_t *mlx_ptr, void (*fct)(void *), void *param)
{
  mlx_ptr->loop_hook = fct;
  mlx_ptr->loop_hook_data = param;
  return (0);
}