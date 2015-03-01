----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "moai.png" )
gfxQuad:setRect ( -64, -64, 64, 64 )

prop = MOAIProp2D.new ()
prop:setDeck ( gfxQuad )
prop:setLoc ( 0, 80 )
layer:insertProp ( prop )

font = MOAIFont.new ()
font:loadFromTTF ( "arialbd.ttf", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?!", 12, 163 )

textbox = MOAITextBox.new ()
textbox:setFont ( font )
textbox:setRect ( -160, -80, 160, 80 )
textbox:setLoc ( 0, -100 )
textbox:setYFlip ( true )
textbox:setAlignment ( MOAITextBox.CENTER_JUSTIFY )
layer:insertProp ( textbox )

textbox:setString ( "Moai has installed correctly! Check out the samples folder.\n<c:0F0>Meow.<c>" )
textbox:spool ()

function twirlingTowardsFreedom ()
	while true do
		MOAIThread.blockOnAction ( prop:moveRot ( 360, 1.5 ))
		MOAIThread.blockOnAction ( prop:moveRot ( -360, 1.5 ))
	end
end

thread = MOAIThread.new ()
thread:run ( twirlingTowardsFreedom )


local function printf ( ... )
	print ( string.format ( ... ))
end 

print ( MOAIInputMgr.configuration )

----------------------------------------------------------------
-- keyboard events

function onKeyboardEvent ( key, down )

	if down == true then
		printf ( "keyboard: %d down\n", key )
	else
		printf ( "keyboard: %d up\n", key )
	end
end
if MOAIInputMgr.device then
	MOAIInputMgr.device.keyboard:setCallback ( onKeyboardEvent )
else
	print( "No Keyboard")
end

----------------------------------------------------------------
-- pointer events

function onPointerEvent ( x, y )
	printf ( "pointer: %d %d\n", x, y )
end

MOAIInputMgr.device.pointer:setCallback ( onPointerEvent )

----------------------------------------------------------------
-- mouse left button events

function onMouseLeftEvent ( down )

	if down == true then
		printf ( "touch down\n" )
	else
		printf ( "touch up up\n" )
	end
end

MOAIInputMgr.device.touch:setCallback ( onMouseLeftEvent )

