--==============================================================
-- setup
--==============================================================


function table.contains(table, element)
  for _, value in pairs(table) do
    if value == element then
      return true
    end
  end
  return false
end

--==============================================================
-- args
--==============================================================
local hostconfig = {
    AppName = "Moai Template",
    CompanyName = "Zipline Games",
    LuaSrc = MOAI_SDK_HOME..'samples/hello-moai'
}


local config = {}

config.OUTPUT_DIR                      = INVOKE_DIR..'hosts/windows-phone/vs2013/'
config.LIB_SOURCE                      = MOAI_SDK_HOME..'lib/windowsphone/vs2013/'
config.USE_SYMLINK                     = false

MOAIFileSystem.setWorkingDirectory(INVOKE_DIR)

local configFile = false
for i, escape, param, iter in util.iterateCommandLine ( arg or {}) do

	if escape == 's' or escape == 'use-symlink' then
		config.USE_SYMLINK = true
	end
	if (param) then
		if escape == 'o' or escape == 'output-dir' then
			config.OUTPUT_DIR = MOAIFileSystem.getAbsoluteDirectoryPath(param)
		end

    if escape == 'l' or escape == 'lib-source' then
			config.LIB_SOURCE = MOAIFileSystem.getAbsoluteDirectoryPath(param)
		end
    
    if escape == 'c' or escape == 'config' then
      configFile = MOAIFileSystem.getAbsoluteFilePath(param)
    end
    
	end
end

--==============================================================
-- actions
--==============================================================

local copyhostfiles 
local copylib
local linklib
local applyConfigFile
local configureHost

copyhostfiles = function() 
	local output = config.OUTPUT_DIR
	print("Creating ",output)
    MOAIFileSystem.affirmPath(output)


    
	for entry in util.iterateFiles( MOAI_SDK_HOME..'host-templates/windowsphone/vs2013', false, true) do
			local fullpath = string.format ( '%s/%s',MOAI_SDK_HOME..'host-templates/windowsphone/vs2013' , entry )
			print( string.format( '%s -> %s', fullpath, output..entry ))
			MOAIFileSystem.copy(fullpath, output..entry)
	end

    local hostsrc = MOAI_SDK_HOME..'src/host-windows-phone/'
    local hostmodules = MOAI_SDK_HOME..'src/host-modules/'
    MOAIFileSystem.copy(hostsrc, output..'Moai Template.WindowsPhone/src')
    MOAIFileSystem.copy(hostmodules, output..'host-src/host-modules')

    --don't want these ones
    MOAIFileSystem.deleteFile(output..'host-modules/aku_modules_ios.h')
    MOAIFileSystem.deleteFile(output..'host-modules/aku_modules_ios_config.h')
    MOAIFileSystem.deleteFile(output..'host-modules/aku_modules_ios.mm')
    MOAIFileSystem.deleteFile(output..'host-modules/aku_modules_android.h')
    MOAIFileSystem.deleteFile(output..'host-modules/aku_modules_android_config.h')
    MOAIFileSystem.deleteFile(output..'host-modules/aku_modules_android.cpp')

end

configureHost = function()

  local output = config.OUTPUT_DIR
  --get lua folder path (relative to xcode project)
  local fullLua = MOAIFileSystem.getAbsoluteDirectoryPath(hostconfig['LuaSrc'])
  local relativeLua = MOAIFileSystem.getRelativePath( fullLua, output..'Moai Template.WindowsPhone/' )
  local relativeLua = string.match(relativeLua, "(.*)/$") --strip trailing slash

  print("\n\nApplying config from "..configFile..":")
  for k,v in pairs(hostconfig) do
    print (k..": ", v)
  end
  
print("config dest",output..'Moai Template.WindowsPhone/Moai Template.vcxproj')
util.replaceInFiles ({
  [ output..'Moai Template.WindowsPhone/Moai Template.WindowsPhone.vcxproj' ] = {
      --our lua path
      ['lua\\%*%*\\%*.%*'] = string.gsub(relativeLua.."/**/*.*","/","\\"),
      --our app name
      ['Moai_Template'] = string.gsub(hostconfig['AppName']," ","_")
  },
  [ output..'Moai Template.sln' ] = {
      ['Moai Template'] = hostconfig['AppName']
  },
  [ output..'Moai Template.WindowsPhone/Package.appxmanifest'] = {
      ['Moai Template'] = hostconfig['AppName'],
      ['Moai_Template'] = string.gsub(hostconfig['AppName']," ","_"),
      ['Zipline Games'] = hostconfig['CompanyName']
  }
  
})
 
 
 if (hostconfig['AppName'] ~= 'Moai Template') then
   --rename the solution
   MOAIFileSystem.copy(output..'Moai Template.sln', output..hostconfig['AppName']..'.sln')
   MOAIFileSystem.deleteFile(output..'Moai Template.sln')
   
   --rename the windows phone project 
   MOAIFileSystem.copy(output..'Moai Template.WindowsPhone/Moai Template.WindowsPhone.vcxproj', 
                       output..'Moai Template.WindowsPhone/'..hostconfig['AppName']..'.WindowsPhone.vcxproj')  
   MOAIFileSystem.deleteFile(output..'Moai Template.WindowsPhone/Moai Template.WindowsPhone.vcxproj')
   MOAIFileSystem.copy(output..'Moai Template.WindowsPhone/Moai Template.WindowsPhone.vcxproj.filters', 
                       output..'Moai Template.WindowsPhone/'..hostconfig['AppName']..'.WindowsPhone.vcxproj.filters')  
   MOAIFileSystem.deleteFile(output..'Moai Template.WindowsPhone/Moai Template.WindowsPhone.vcxproj.filters')
   
   --rename the project too
   MOAIFileSystem.copy(output..'Moai Template.WindowsPhone', output..hostconfig['AppName']..'.WindowsPhone')
   MOAIFileSystem.deleteDirectory(output..'Moai Template.WindowsPhone', true)
 end 

 
end


copylib = function() 
	MOAIFileSystem.copy(config.LIB_SOURCE, config.OUTPUT_DIR..'libmoai' )
end

linklib = function() 
	local isWindows = MOAIEnvironment.osBrand == 'Windows'
	local cmd = isWindows and 'mklink /D "'..config.OUTPUT_DIR..'libmoai" "'..config.LIB_SOURCE..'"' 
	                      or 'ln -s "'..config.LIB_SOURCE..'" "'..config.OUTPUT_DIR..'libmoai"'
	if os.execute(cmd) > 0 then
	   print ("Error creating link, try running as administrator")
	end
end


applyConfigFile = function(configFile)
  util.dofileWithEnvironment(configFile, hostconfig)
  

  --copy host specific settings to main config
  if (hostconfig["HostSettings"] and hostconfig["HostSettings"]["windowsphone"]) then
    for k,v in pairs(hostconfig["HostSettings"]["windowsphone"]) do
      hostconfig[k] = v
    end
  end
  
  hostconfig["HostSettings"] = nil
  
end


applyConfigFile(configFile)

copyhostfiles()

configureHost()


if (config.USE_SYMLINK) then
	linklib()
else
	copylib()
end
