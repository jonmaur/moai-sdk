require ( 'util' )
local generateRom = require('file_packager')

--utils--
function string:split(sep)
    sep = sep or ","
    local fields =  {}
    local pattern = string.format("([^%s]+)", sep)
    self:gsub(pattern, function(c) table.insert(fields,c) end)
    return fields
end


--==============================================================
-- args
--==============================================================

local config = {}

config.OUTPUT_DIR                       = INVOKE_DIR..'sample-index'
config.SAMPLE_SOURCE                      = MOAIFileSystem.getAbsoluteDirectoryPath(MOAI_SDK_HOME..'samples')
config.SAMPLE_WHITELIST = false

MOAIFileSystem.setWorkingDirectory(INVOKE_DIR)

for i, escape, param, iter in util.iterateCommandLine ( arg or {}) do
	
	if (param) then
    if escape == 'w' or escape == 'whitelist' then
      local list = param:split(',')
      config.SAMPLE_WHITELIST = util.arrayToSet(list)
    end
	
    if escape == 'o' or escape == 'output-dir' then
			config.OUTPUT_DIR = MOAIFileSystem.getAbsoluteDirectoryPath(param)
    end

    if escape == 's' or escape == 'sample-source' then
			config.SAMPLE_SOURCE = MOAIFileSystem.getAbsoluteDirectoryPath(param)
		end
	end
  
end

local scriptDir = MOAIFileSystem.getAbsoluteDirectoryPath(SCRIPT_DIR)
--setup player dir
MOAIFileSystem.copy(MOAIFileSystem.getAbsoluteDirectoryPath(scriptDir..'player'),
                    MOAIFileSystem.getAbsoluteDirectoryPath(config.OUTPUT_DIR..'/player'))


--setup lib dir
MOAIFileSystem.copy(MOAIFileSystem.getAbsoluteDirectoryPath(MOAI_SDK_HOME..'lib/html/'),
                    MOAIFileSystem.getAbsoluteDirectoryPath(config.OUTPUT_DIR..'/player/lib'))




local allSamples = MOAIFileSystem.listDirectories ( config.SAMPLE_SOURCE );

local skipList = {
  "run.bat", "run.sh", "thumbs.db"
}

local function dumpRomJs(sampleDir, outfolder)
    local rom = generateRom(sampleDir,skipList)
   -- print("rom:\n", rom.jsonData, "\n", rom.romData)

    MOAIFileSystem.affirmPath(outfolder)
    local outfile = MOAIFileStream.new()
    outfile:open(MOAIFileSystem.getAbsoluteFilePath(outfolder.."/romdata.js"),MOAIFileStream.READ_WRITE_NEW )
    
    outfile:write('romJson=')
    outfile:write(rom.jsonData)
    outfile:write(";\n")
    
    outfile:write('romData="')
    outfile:write(rom.romData)
    outfile:write('";')
    outfile:close()  
end

local sampleTemplate = MOAIFileSystem.loadFile(scriptDir.."/samplepage.html")

local function dumpSamplePage(sample, sampleDir, outfolder) 
   local sampleOutput = sampleTemplate:gsub("@SAMPLENAME@",sample)
   MOAIFileSystem.saveFile(MOAIFileSystem.getAbsoluteFilePath(outfolder.."/index.html"),sampleOutput)
end

local function dumpSampleList(samples)
  local list = "var samplelist=["
  for k,sample in pairs(samples) do
    list = list..'"'..sample..'",'
  end
  list = list.."];" 
  
  local outfile = MOAIFileSystem.getAbsoluteFilePath(config.OUTPUT_DIR.."/player/samplelist.js")
  MOAIFileSystem.saveFile(outfile, list)
end

local samplesProcessed = {}
for k,sample in ipairs(allSamples) do
  
  if not config.SAMPLE_WHITELIST or config.SAMPLE_WHITELIST[sample] then
    
    local sampleDir = MOAIFileSystem.getAbsoluteDirectoryPath(config.SAMPLE_SOURCE.."/"..sample)
    local outfolder = MOAIFileSystem.getAbsoluteDirectoryPath(config.OUTPUT_DIR.."/"..sample)
    table.insert(samplesProcessed, sample)
    
    print("building sample ",sample,"in",sampleDir)
    --dump rom js
    dumpRomJs(sampleDir, outfolder)
    
    --dump index.html
    dumpSamplePage(sample, sampleDir, outfolder)
    
  end
  
  
end

dumpSampleList(samplesProcessed)






