import SimpleGUICS2Pygame.simpleguics2pygame as simplegui
import random
def convert_unit(val,tailstr):
	res=str(val)+" "+tailstr
	if val>1:
		res=res+"s"
	return res
def convert(val):
	dollars=int(val)
	cents=round(100*(val-dollars))
	
	d_string=convert_unit(dollars,"dollar")
	c_string=convert_unit(cents,"cent")
	if dollars==0 and cents==0:
		return "you are broke"
	elif dollars==0:
		return c_string
	elif cents==0:
		return d_string
	else:
		return d_string+"and"+c_string

print convert(0.10)
print convert(12.23)
print convert(11.00)
value=10
position=[100,100]
def input_handle(text):
	global value
	value=float(text)
def draw(canvas):
	canvas.draw_text(convert(value),position,24,"white")
	canvas.draw_circle([150,150],10,10,"Red")
def timer_handle():
	x=random.randrange(1,300)
	y=random,randrange(1,200)
	global position
	position[0]=x
	position[1]=y
frame=simplegui.create_frame("test",300,200)
frame.set_draw_handler(draw)
frame.add_input("Enter Value",input_handle,100)
timer=simplegui.create_timer(1000,timer_handle)
timer.start()
frame.start()
