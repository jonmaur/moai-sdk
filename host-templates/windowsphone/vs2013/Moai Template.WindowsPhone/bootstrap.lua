io.output():setvbuf( "no" ) 
print = function ( ... )
		
        local arguments = {...} 
		local argCount = #arguments
		
		if argCount == 0 then
			MOAILogMgr.log ( "" )
			return
		end
		
		local output = tostring ( arguments [ 1 ])
		
		for i = 2, argCount do
			output = output .. "\t" .. tostring ( arguments [ i ])
		end
		
		MOAILogMgr.log ( output )
	end

	print ( "load:" .. "\t" .. "running main.lua" )
	

dofile("main.lua")