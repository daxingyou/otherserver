--------------------------------------------------------
-- ����: ��ֵ��������
-- ʱ��: 2012-06-07
--------------------------------------------------------
local function doValueLimitCheck(tableName, csvTable, args)
	local fieldName = args["field"];
	local minV = tonumber(args["min"]);
	local maxV = tonumber(args["max"]);
	local fieldList = csvTable[1];
	local fieldIndex = nil
	for i = 1, table.getn(fieldList) do
		if fieldList[i] == fieldName then
			fieldIndex = i
			break
		end
	end
	
	if fieldIndex == nil then
		return -1, "ValueLimit���ʧ��:���ݵ�["..tableName.."]û�и���:"..fieldName
	end
	
	local fieldType = csvTable[2][fieldIndex];
	if fieldType ~= "int" and fieldType ~= "float" then
		return -1, "ValueLimit���ʧ��:["..tableName.."]����["..fieldName.."]���Ͳ�����ֵ�ͣ����ܼ��"
	end
	
	for i = 3, table.getn(csvTable) do
		local valueString = csvTable[i][fieldIndex];
		local value = 0;
		if string.len(valueString) > 0 then
			value = tonumber(valueString);
		end
		
		if value == nil or value > maxV or value < minV then
			return -1, "ValueLimit���ʧ��:���ݵ�:["..tableName.."]["..fieldName.."]��ֵ������,����:["..valueString.."]Ҫ����ֵ��Χ["..minV..", "..maxV.."]"
		end
	end
	
	return 1, "OK"
end


local function makeValueLimitCheck(tableName, args)
	return function()
		local tbName = tableName;
		local fieldName = args["field"];
		logCheckMsg("��ʼ��ֵ��Χ���:["..tableName.."]["..fieldName.."]");
		local csvTable = getCsvTable(tableName);
		return doValueLimitCheck(tbName, csvTable, args)
	end
end

function ValueLimit_AddCheck(tableName, args)
	addCheckItem(makeValueLimitCheck(tableName, args) )
end