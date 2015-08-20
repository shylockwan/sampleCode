import SimpleGUICS2Pygame.simpleguics2pygame as simplegui
import random
time_stamp=0
def format(t):
	if not str(t).isdigit():
		return "wrong input"
	min_=int(int(t)/600)
	sec_=(t%600)
	if sec_>99:
		sec_string=str(int(sec_/10))
	else:	
		sec_string="0"+str(int(sec_/10))
	return str(min_)+":"+sec_string+"."+str(int(sec_%10))
def input_handle(text):
	pass
def timer_handle():
	pass
def draw(canvas):
	pass
def start():
	timer.start()
def stop():
	timer.stop()
def reset():
	timer.start()
print format("adsfa")
print format(400)
print format("40a")
frame=simplegui.create_frame("test",300,200)
frame.add_button("start game",start,100)
frame.add_button("start game",stop,100)
frame.add_button("start game",reset,100)
frame.set_draw_handler(draw)
frame.add_input("Enter Value",input_handle,100)
timer=simplegui.create_timer(100,timer_handle)

frame.start()

	