import SimpleGUICS2Pygame.simpleguics2pygame as simplegui
import random
import math
clock=0
def startGame():
	print "please input a num:"
def timeClock():
	global clock
	print clock
	clock+=1
frame=simplegui.create_frame("GuessNum",200,100)
frame.add_button("start game",startGame,100)
timer=simplegui.create_timer(1000,timeClock)
timer.start()
frame.start()