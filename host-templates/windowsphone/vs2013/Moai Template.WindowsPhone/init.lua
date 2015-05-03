package.path = "?;?.lua"

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


local superError = error
	
error = function ( message, level )

	print ( "error: " .. message )
	print ( debug.traceback ( "", 2 ))
	superError ( message, level or 1 )
end