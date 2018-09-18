--------------------------------------------------------
-- ����: IDΨһ�Լ����
-- ʱ��: 2012-06-07
--------------------------------------------------------

local function doUniqueCheck(tableName, csvTable, args)
	local fieldName = args["field"];
	local fieldList = csvTable[1];
	local fieldIndex = nil
	for i = 1, table.getn(fieldList) do
		if fieldList[i] == fieldName then
			fieldIndex = i
			break
		end
	end
	
	if fieldIndex == nil then
		return -1, "Unique���ʧ��:���ݵ�["..tableName.."]û�и���:"..fieldName
	end
	
	local tmpTb = {}
	for i = 3, table.getn(csvTable) do
		local value = csvTable[i][fieldIndex];
		if tmpTb[value]  ~= nil then
			return -1, "Unique���ʧ��:���ݵ�["..tableName.."]["..fieldName.."]��"..i.."�к͵�"..tmpTb[value].."��������ͬ:"..value
		end
		tmpTb[value] = i
	end
	
	return 1, "OK"
end


local function makeUniqueCheck(tableName, args)
	return function()
		local fieldName = args["field"];
		logCheckMsg("��ʼ��ֵΨһ(Unique)�Լ��:["..tableName.."]["..fieldName.."]");
		local csvTable = getCsvTable(tableName);
		
		return doUniqueCheck(tableName, csvTable, args)
	end
end

function Unique_AddCheck(tableName, args)
	addCheckItem(makeUniqueCheck(tableName, args) )
end