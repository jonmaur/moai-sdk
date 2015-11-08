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




local function indexKeywords(index, sample, doc)
  
  local function addToIndex(token)
    if not index[token] then
      index[token] = {}
    end
    
    if not index[token][sample] then
      index[token][sample] = 1
    else
      index[token][sample] = index[token][sample] + 1
    end
    
  end
  
  
  for m in doc:gmatch('MOAI%w+%.*[%w_%-]+') do
    --first index whole word
    addToIndex(m)
    
    if (m == "MOAIAction.EVENT" and sample == "font-glyph") then
      print("found MOAIAction.event in sample font-glyph")
      print(doc)
      os.exit(1)
    end
    
    --split on . and add both
    found, _, klass, method = m:find("(%w+)%.([%w_%-]+)")
    if found then
      addToIndex(klass)
      addToIndex(method)
    end
    
  end
  

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

local function dumpSampleIndex(index)
  local indexJs = "var sampleindex = "..MOAIJsonParser.encode(index )
  local outfile = MOAIFileSystem.getAbsoluteFilePath(config.OUTPUT_DIR.."/player/sampleindex.js")
  MOAIFileSystem.saveFile(outfile, indexJs)
end



local function buildSampleBrowser()
  local samplesProcessed = {}
  local moaikeywords = {}
  for k,sample in ipairs(allSamples) do
    
    if not config.SAMPLE_WHITELIST or config.SAMPLE_WHITELIST[sample] then
      
      local sampleDir = MOAIFileSystem.getAbsoluteDirectoryPath(config.SAMPLE_SOURCE.."/"..sample)
      local outfolder = MOAIFileSystem.getAbsoluteDirectoryPath(config.OUTPUT_DIR.."/"..sample)
      table.insert(samplesProcessed, sample)
      
      print("building sample ",sample,"in",sampleDir)
      --dump rom js
      dumpRomJs(sampleDir, outfolder)
      
      --dump index.html
      --dumpSamplePage(sample, sampleDir, outfolder)
      
      --index main.lua
      if (MOAIFileSystem.checkFileExists(sampleDir.."/main.lua")) then
        local main = MOAIFileSystem.loadFile(sampleDir.."/main.lua")
        indexKeywords(moaikeywords, sample, main)
      end
      
      
    end
    
    
  end
  
  dumpSampleList(samplesProcessed)
  dumpSampleIndex(moaikeywords)
end


buildSampleBrowser()




