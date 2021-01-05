package main

//import "fmt"
import "time"
import "math/rand"
import "github.com/veandco/go-sdl2/sdl"


type Screen struct {
	h int32
	w int32
	name string
	exit bool
	window *sdl.Window
	renderer *sdl.Renderer
}

func (screen *Screen) open() {
	var err error
	rand.Seed(time.Now().UnixNano())

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

func (screen *Screen) set_draw_color(color sdl.Color) {
	screen.renderer.SetDrawColor(
		color.R,
		color.G,
		color.B,
		color.A)
}

func (screen *Screen) close() {
	screen.renderer.Destroy()
	screen.window.Destroy()
	sdl.Quit()
}

type Racket struct {
	box sdl.Rect
	speed sdl.Point
	speed_max int32
}

type Ball struct {
	box sdl.Rect
	state int32
	speed sdl.Point
	speed_max int32
}

type Layout struct {
	screen *Screen

	padding int32
	
	racket_w int32
	racket_h int32

	ball_w int32
	ball_h int32

	speed_limit_racket int32
	speed_limit_ball int32

	middle sdl.Point
}


func (l Layout) build_layout(player *Racket, cpu *Racket, ball *Ball) {
	player.box = sdl.Rect{
		X: l.padding,
		Y: l.middle.Y - l.racket_h/2,
		W: l.racket_w,
		H: l.racket_h}
	player.speed = sdl.Point{}
	player.speed_max = l.speed_limit_racket


	cpu.box = sdl.Rect{
		X: l.screen.w - l.padding - l.racket_w,
		Y: l.middle.Y - l.racket_h/2,
		W: l.racket_w,
		H: l.racket_h}
	cpu.speed = sdl.Point{}
	cpu.speed_max = l.speed_limit_racket


	ball.box = sdl.Rect{
		X: l.middle.X - l.ball_w/2,
		Y: l.middle.Y - l.ball_h/2,
		W: l.ball_w,
		H: l.ball_h}
	ball.speed = sdl.Point{}
	ball.speed_max = l.speed_limit_ball
}


func main() {
	
	black := sdl.Color{0, 0, 0, 255}
	white := sdl.Color{255, 255, 255, 255}

	screen := Screen{w: 640, h: 480, name: "Pong", exit: false}
	screen.open()

	keys := sdl.GetKeyboardState()


	layout := Layout{
		screen: &screen,
		padding: 100,
		racket_w: 20,
		racket_h: 100,
		ball_w: 30,
		ball_h: 30,
		speed_limit_racket: 10,
		speed_limit_ball: 5,
		middle: sdl.Point{X: screen.w/2, Y: screen.h/2}}

	player := Racket{}
	cpu := Racket{}
	ball := Ball{}

	layout.build_layout(&player, &cpu, &ball)

	rand_val_x := rand.Intn(2)
	rand_val_y := rand.Intn(2)

	if (rand_val_x == 0) {
		ball.speed.X = ball.speed_max
	} else {
		ball.speed.X = -ball.speed_max
	}

	if (rand_val_y == 0) {
		ball.speed.Y = ball.speed_max
	} else {
		ball.speed.Y = -ball.speed_max
	}

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




		// Update objects
		player.box.X += player.speed.X
		player.box.Y += player.speed.Y
		player.speed.X = 0
		player.speed.Y = 0

		cpu.box.X += cpu.speed.X
		cpu.box.Y += cpu.speed.Y
		cpu.speed.X = 0
		cpu.speed.Y = 0

		ball.box.X += ball.speed.X
		ball.box.Y += ball.speed.Y

		// Render
		screen.set_draw_color(black)
		screen.renderer.Clear()

		screen.set_draw_color(white)
		screen.renderer.FillRects([]sdl.Rect{player.box, cpu.box, ball.box})

		screen.renderer.Present()
	}

	screen.close()
}
