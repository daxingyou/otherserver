--------------------------------------------------------
-- ����: ͨ�����ݸ�ʽ���
-- ʱ��: 2012-06-07
--------------------------------------------------------

local g_tyErrmsgHead = "]�������ͼ��ʧ�ܣ�"
local g_typeDefine = {}
g_typeDefine["int"]= 1;
g_typeDefine["string"]= 1;
g_typeDefine["float"]= 1;

-- ������д����ΪĬ������
local function chceckSingleType(data, tyName)
	if tyName == "int" and tonumber(data) == nil and string.len(data)~=0 then
		return false
	end
	
	if tyName == "float" and tonumber(data) == nil and string.len(data)~=0 then
		return false;
	end
	
	if data == nil then
		return false;
	end
	
	return true
end

local function csvTypeCheckImp(tbName, csvTable)
	if csvTable == nil then
		return -1, "û���ҵ�:"..tbName
	end

	local filedList = csvTable[1];
	local tpList = csvTable[2];
	
	-- �Ƿ��б�������Ͷ���
	if filedList == nil or tpList == nil then
		return -1, "["..tbName..g_tyErrmsgHead.."����Ϊ�գ��������Ͷ���Ϊ��"
	end
	
	-- ��������Ͷ��������Ƿ�һ��
	if table.getn(filedList) ~= table.getn(tpList) then
		return -1, "["..tbName..g_tyErrmsgHead.."������"..table.getn(filedList).."�У����Ͷ���ֻ��"..table.getn(tpList).."��"
	end
	
	-- ���Ͷ����Ƿ�Ϸ�
	for i = 1, table.getn(tpList) do
		local tyName = tpList[i]
		if g_typeDefine[tyName] ~= 1 then
			return -1, "["..tbName..g_tyErrmsgHead.."["..filedList[i].."]���Ͷ���Ƿ�:"..tostring(tyName)
		end
	end
	
	-- ���ÿһ�е������Ƿ�Ϸ�
	for i = 3, table.getn(csvTable) do
		local rowData = csvTable[i]
		
		-- ����֤����Ŀ�Ƿ���ȷ
		if table.getn(rowData) ~= table.getn(tpList) then
			return -1, "["..tbName..g_tyErrmsgHead.."��"..i.."������ֻ��"..table.getn(rowData).."�У�ʵ����Ҫ:"..table.getn(tpList).."��"
		end
		
		for field = 1, table.getn(tpList) do
			result = chceckSingleType(rowData[field], tpList[field]);
			if result == false then
				return -1, "["..tbName..g_tyErrmsgHead.."��"..i.."��"..field.."���������ʹ���:"..tostring(rowData[field]).."����:"..tpList[field]
			end
		end
	end
	
	return 1, "OK"
end

function makeTypeCheck(tableName)
	return function()
		local tbName = tableName;
		logCheckMsg("��ʼ�������ͼ��:"..tableName);
		local csvTable = getCsvTable(tableName);
		local  result, errmsg = csvTypeCheckImp(tableName, csvTable)
		if result >= 0 then
			logCheckMsg("���ͼ��ɹ�:"..tableName);
		end
		return result, errmsg
	end
end

function CheckType_AddCheck(tableName, args)
	addCheckItem(makeTypeCheck(tableName) )
end

