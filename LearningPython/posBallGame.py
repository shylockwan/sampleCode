# Implementation of classic arcade game Pong
import SimpleGUICS2Pygame.simpleguics2pygame as simplegui
import random

# initialize globals - pos and vel encode vertical info for paddles
WIDTH = 600
HEIGHT = 400       
BALL_RADIUS = 20
PAD_WIDTH = 8
PAD_HEIGHT = 80
HALF_PAD_WIDTH = PAD_WIDTH / 2
HALF_PAD_HEIGHT = PAD_HEIGHT / 2
LEFT = False
RIGHT = True
# initialize ball_pos and ball_vel for new bal in middle of table
# if direction is RIGHT, the ball's velocity is upper right, else upper left
def spawn_ball():
    global ball_pos, ball_vel # these are vectors stored as lists
    ball_pos=[WIDTH/2,HEIGHT/2]
    ball_vel=[5,0]

# define event handlers
def new_game():
    global paddle1_pos, paddle2_pos, paddle1_vel, paddle2_vel  # these are numbers
    global score1, score2  # these are ints
    score1=0;score2=0
    spawn_ball()
    paddle1_pos=[0+HALF_PAD_WIDTH,HEIGHT/2];paddle2_pos=[WIDTH-HALF_PAD_WIDTH,HEIGHT/2]
    paddle1_vel=0;paddle2_vel=0
	
	

def draw(canvas):
	global score1, score2, paddle1_pos, paddle2_pos, ball_pos, ball_vel
 
        
    # draw mid line and gutters
	canvas.draw_line([WIDTH / 2, 0],[WIDTH / 2, HEIGHT], 1, "White")
	canvas.draw_line([PAD_WIDTH, 0],[PAD_WIDTH, HEIGHT], 1, "White")
	canvas.draw_line([WIDTH - PAD_WIDTH, 0],[WIDTH - PAD_WIDTH, HEIGHT], 1, "White")
        
    # update ball
	
	ball_pos[0]=ball_pos[0]+ball_vel[0]
	ball_pos[1]=ball_pos[1]+ball_vel[1]
           
    # draw ball
	canvas.draw_circle(ball_pos,BALL_RADIUS,BALL_RADIUS,"Red")
    # update paddle's vertical position, keep paddle on the screen
	paddle1_pos[1]+=paddle1_vel
	paddle2_pos[1]+=paddle2_vel
	if paddle1_pos[1] > HEIGHT-HALF_PAD_HEIGHT:
		paddle1_pos[1] = HEIGHT-HALF_PAD_HEIGHT
	if paddle1_pos[1] < 0+HALF_PAD_HEIGHT:
		paddle1_pos[1] = 0+HALF_PAD_HEIGHT
	if paddle2_pos[1] > HEIGHT-HALF_PAD_HEIGHT:
		paddle2_pos[1] = HEIGHT-HALF_PAD_HEIGHT
	if paddle2_pos[1] < 0+HALF_PAD_HEIGHT:
		paddle2_pos[1] = 0+HALF_PAD_HEIGHT
	# draw paddles
	canvas.draw_line([0, paddle1_pos[1]-HALF_PAD_HEIGHT],[PAD_WIDTH, paddle1_pos[1]-HALF_PAD_HEIGHT], 1, "Blue")
	canvas.draw_line([0, paddle1_pos[1]+HALF_PAD_HEIGHT],[PAD_WIDTH, paddle1_pos[1]+HALF_PAD_HEIGHT], 1, "Blue")
	canvas.draw_line([PAD_WIDTH, paddle1_pos[1]-HALF_PAD_HEIGHT],[PAD_WIDTH, paddle1_pos[1]+HALF_PAD_HEIGHT], 1, "Blue")
	
	canvas.draw_line([WIDTH, paddle2_pos[1]-HALF_PAD_HEIGHT],[WIDTH-PAD_WIDTH, paddle2_pos[1]-HALF_PAD_HEIGHT], 1, "Blue")
	canvas.draw_line([WIDTH, paddle2_pos[1]+HALF_PAD_HEIGHT],[WIDTH-PAD_WIDTH, paddle2_pos[1]+HALF_PAD_HEIGHT], 1, "Blue")
	canvas.draw_line([WIDTH-PAD_WIDTH, paddle2_pos[1]-HALF_PAD_HEIGHT],[WIDTH-PAD_WIDTH, paddle2_pos[1]+HALF_PAD_HEIGHT], 1, "Blue")
	
	
    # determine whether paddle and ball collide
	coli_error=3
	if abs(ball_pos[0]-PAD_WIDTH-BALL_RADIUS)<coli_error and abs(ball_pos[1]-paddle1_pos[1])<HALF_PAD_HEIGHT:
	    ball_vel[0]=(-ball_vel[0])
	if abs(ball_pos[0]-(WIDTH-PAD_WIDTH-BALL_RADIUS))<coli_error and abs(ball_pos[1]-paddle2_pos[1])<HALF_PAD_HEIGHT:
		ball_vel[0]=(-ball_vel[0])
	if ball_pos[1]-BALL_RADIUS==0 or ball_pos[1]+BALL_RADIUS==HEIGHT:
		ball_vel[1]=(-ball_vel[1])
		
    # draw scores
	canvas.draw_text(str(score1), [200,200], 50, "Red")
	canvas.draw_text(str(score2), [400,200], 50, "Red")
	if ball_pos[0]> WIDTH-PAD_WIDTH:
		score2+=1
		spawn_ball()
	elif ball_pos[0]<PAD_WIDTH:
		score1+=1
		spawn_ball()
	
	
	
def keydown(key):
	global paddle1_vel, paddle2_vel
	delta=5
	if key == simplegui.KEY_MAP['w']:
		paddle1_vel-=delta
	elif key == simplegui.KEY_MAP["s"]:
		paddle1_vel+=delta
	elif key == simplegui.KEY_MAP["down"]:
		paddle2_vel+=delta
	elif key == simplegui.KEY_MAP["up"]:
		paddle2_vel-=delta
		
def keyup(key):
    global paddle1_vel, paddle2_vel
	
    paddle1_vel=0;paddle2_vel=0


# create frame
frame = simplegui.create_frame("Pong", WIDTH, HEIGHT)
frame.set_draw_handler(draw)
frame.set_keydown_handler(keydown)
frame.set_keyup_handler(keyup)


# start frame
new_game()
frame.start()
