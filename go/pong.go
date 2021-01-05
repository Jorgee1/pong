package main

//import "fmt"
import "github.com/veandco/go-sdl2/sdl"


type Screen struct {
	h int32
	w int32
	name string
	exit bool
	window *sdl.Window
	renderer *sdl.Renderer
	clear_color sdl.Color
}

func (screen *Screen) init() {
	var err error
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

}

func (screen *Screen) clear() {
	screen.renderer.SetDrawColor(
		screen.clear_color.R,
		screen.clear_color.G,
		screen.clear_color.B,
		screen.clear_color.A)
	screen.renderer.Clear()
}

func (screen *Screen) destroy() {
	screen.renderer.Destroy()
	screen.window.Destroy()
}

type Racket struct {
	box sdl.Rect
	speed sdl.Point
	speed_max int32
}

type Ball struct {
	box sdl.Rect
	speed sdl.Point
	speed_max int32
}

type Layout struct {
	padding int32
	
	racket_w int32
	racket_h int32

	ball_w int32
	ball_h int32

	speed_limit_racket int32
	speed_limit_ball int32

	middle sdl.Point
}

/*
func (l Layout) build_layout() {

}
*/

func main() {
	black := sdl.Color{0, 0, 0, 255}
	white := sdl.Color{255, 255, 255, 255}

	screen := Screen{w: 640, h: 480, name: "Pong", exit: false, clear_color: black}
	screen.init()
	keys := sdl.GetKeyboardState()


	layout := Layout{
		padding: 100,
		racket_w: 20,
		racket_h: 100,
		ball_w: 30,
		ball_h: 30,
		speed_limit_racket: 10,
		speed_limit_ball: 20,
		middle: sdl.Point{X: screen.w/2, Y: screen.h/2}}

	player := Racket{}
	player.box = sdl.Rect{
		X: layout.padding,
		Y: layout.middle.Y - layout.racket_h/2,
		W: layout.racket_w,
		H: layout.racket_h}
	player.speed = sdl.Point{0, 0}
	player.speed_max = 10

	cpu := Racket{}
	cpu.box = sdl.Rect{
		X: screen.w - layout.padding - layout.racket_w,
		Y: layout.middle.Y - layout.racket_h/2,
		W: layout.racket_w,
		H: layout.racket_h}
	cpu.speed = sdl.Point{0, 0}
	cpu.speed_max = 10

	ball := Ball{}
	ball.box = sdl.Rect{
		X: layout.middle.X - layout.ball_w/2,
		Y: layout.middle.Y - layout.ball_h/2,
		W: layout.ball_w,
		H: layout.ball_h}
	ball.speed = sdl.Point{0, 0}
	ball.speed_max = 20

	for screen.exit != true {
		for {
			event := sdl.PollEvent()

			if event == nil {
				break
			} else if event.GetType() == sdl.QUIT {
				screen.exit = true
			}
		}

		// Check input
		if keys[sdl.SCANCODE_W] == 1 {
			player.speed.Y = -player.speed_max
		} else if keys[sdl.SCANCODE_S] == 1 {
			player.speed.Y =  player.speed_max
		} else {
			player.speed.Y = 0
		}

		// Logistic




		// update objects
		player.box.X += player.speed.X
		player.box.Y += player.speed.Y

		cpu.box.X += cpu.speed.X
		cpu.box.Y += cpu.speed.Y

		ball.box.X += ball.speed.X
		ball.box.Y += ball.speed.Y

		// Render
		screen.clear()

		screen.renderer.SetDrawColor(
			white.R,
			white.G,
			white.B,
			white.A)
		screen.renderer.FillRects([]sdl.Rect{player.box, cpu.box, ball.box})

		screen.renderer.Present()
	}

	screen.destroy()

	sdl.Quit()
}
