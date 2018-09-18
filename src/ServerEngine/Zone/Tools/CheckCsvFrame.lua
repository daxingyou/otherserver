--------------------------------------------------------
-- ����: ���ݵ������
-- ʱ��: 2012-06-07
--------------------------------------------------------

dofile("csv.lua")
dofile("xml.lua")
if table.getn(arg) ~= 1 then
	print("useage:[dataDir]")
	return;
end

-- csv���ݵ�Ŀ¼
local g_dataDir = arg[1]; 

-- ��������
local g_checkItem = {}

-- csv����ԭʼ���ݱ�,��Ҫ���������ٸ�������������ִ�У������ظ�����
local g_csvTable = {}
local g_errlog = "checkCsv.log";
local g_errFile = io.open(g_errlog, "wb");

function getCsvTable(tableName)
	if g_csvTable[tableName] == nil then
		g_csvTable[tableName] = parseCsv(g_dataDir.."/"..tableName);
	end
	
	return g_csvTable[tableName]
end

function addCheckItem(checkClosure)
	table.insert(g_checkItem, checkClosure);
end

function logCheckMsg(data)
	g_errFile:write(data.."\n")
	g_errFile:flush();
	print(data)
end

-- ���в�������
function doCheck()
	for i =1, table.getn(g_checkItem) do
		local f = g_checkItem[i]
		local result, errmsg = f()
		if result < 0 then
			logCheckMsg(errmsg)
			g_errFile:flush();
			g_errFile:close();
			os.exit(-1);
		end
	end
	
	logCheckMsg("���㿴����һ�䣬˵�����в���ͨ���ˣ�");
end

-- ���ز�����������XML
function loadDataCheckConf(fileName)
	print("-------------")
	local confTable = parseXml(fileName);
	if confTable == nil then
		logCheckMsg("δ�ҵ����ݵ���������ļ�:"..tostring(fileName) );
		os.exit(-1);
	end
	
	if confTable.n ~= 2 then
		logCheckMsg(fileName.."��ʽ����");
		os.exit(-1);
	end
	
	confTable = confTable[2]
	if confTable.label ~= "tablecheck" then
		logCheckMsg("��Ҫ����tablecheck");
		os.exit(-1);
	end
	
	if confTable[1] == nil then
		logCheckMsg("û���ҵ����Թ��ܲ��");
		os.exit(-1);
	end
	
	-- ���ز��ģ��
	local pluginTb = confTable[1];
	for i = 1, pluginTb.n do
		local pluginName = pluginTb[i].args["name"];
		local pluginFile = "plugin/"..pluginName..".lua"
		logCheckMsg("��ʼ���ز��:"..pluginFile)
		dofile(pluginFile)
		logCheckMsg("�������ز��:"..pluginFile)
	end
	
	-- ���ز��Ա�
	if confTable[2].label ~= "tables"  then
		logCheckMsg("û������Ҫ�������ݱ�")
		return;
	end
	
	-- ���ؾ�����Ա�
	local checkTbs = confTable[2];
	print("lable:"..checkTbs.label)
	for i = 1, checkTbs.n do
		local checkItemTable = checkTbs[i];
		loadSingTableCheck(checkItemTable);
	end
end

function loadSingTableCheck(confTable)
	local tableName = confTable.args["name"];
	logCheckMsg("����["..tableName.."]��������"..(confTable.n).."����")
	for i = 1, confTable.n do
		local singleCheck = confTable[i];
		local checkType = singleCheck.args["type"];
		logCheckMsg("׼��������ݱ�:"..tableName.."������["..checkType.."]");
		g_cmdArgs = singleCheck.args
		local cmdString = checkType.."_AddCheck(\""..tableName.."\",g_cmdArgs)"
		local result, errmsg = pcall(loadstring(cmdString) )
		if result ~= true then
			logCheckMsg("��ӱ����ʧ��:["..tableName.."]["..checkType.."]errmsg:"..errmsg);
		end
	end
end

-- �������,Ĭ���ṩ���ͼ��
--dofile("CheckType.lua")
--dofile("CsvCheckValueLimit.lua")
--loading �߻�/�������õĲ�������
--addCheckItem(makeTypeCheck("test.csv") )

loadDataCheckConf("DataCheck.xml")
doCheck();

