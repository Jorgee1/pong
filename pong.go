package main

import "fmt"
import "github.com/veandco/go-sdl2/sdl"


type Screen struct {
	h int32
	w int32
	name string
	exit bool
	window *sdl.Window
	renderer *sdl.Renderer
}

func main() {
	fmt.Println("HA")
	var err error
	screen := Screen{w: 640, h: 480, name: "Pong", exit: false}

	sdl.Init(sdl.INIT_EVERYTHING)

	screen.window, err = sdl.CreateWindow(
		screen.name,
		sdl.WINDOWPOS_UNDEFINED,
		sdl.WINDOWPOS_UNDEFINED,
		screen.w,
		screen.h,
		sdl.WINDOW_HIDDEN)
	if err != nil { panic(err) }

	screen.renderer, err = sdl.CreateRenderer(
		screen.window, -1,
		sdl.RENDERER_ACCELERATED | sdl.RENDERER_PRESENTVSYNC)
	if err != nil { panic(err) }

	screen.window.Show()


	for screen.exit != true {
		for {
			event := sdl.PollEvent()

			if event == nil {
				break
			} else if event.GetType() == sdl.QUIT {
				screen.exit = true
			}
		}
		screen.renderer.Clear()





		screen.renderer.Present()
	}


	screen.window.Destroy()
	screen.renderer.Destroy()

	sdl.Quit()
}
