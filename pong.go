package main

import "fmt"
import "github.com/veandco/go-sdl2/sdl"

func main(){
	fmt.Println("SDL_INIT")
	sdl.Init(sdl.INIT_EVERYTHING)



	sdl.Quit()
}
