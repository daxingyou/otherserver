

-- ����: ������������Ϣ
function parseCallInfo(callString)
	local tmpCallInfo = {
		funname = "",
		paramTb = {}
	}
	function saveFunName(n, body)
		if string.len(tmpCallInfo.funname) == 0 then
			print("fun:"..n)
			tmpCallInfo.funname = n
		end
		
		return body
	end
	
	function saveParam(n)
		print("param:"..n)
		table.insert(tmpCallInfo.paramTb, n);
	end
	
	print("callString:"..callString)
	callString = string.gsub(callString, "(%d+)#?(.+)", saveFunName)
	print("leftCallString:"..callString)
	string.gsub(callString, "(.-)[#|;]", saveParam)
	return tmpCallInfo;
end

-- ͨ��call,����Ĭ�Ϻ���
function commonCall(callInfo)
		print("functionName:"..callInfo.funname)
		for i=1, table.getn(callInfo.paramTb) do
			print("Param"..i..":"..tostring(callInfo.paramTb[i]))
		end
end


----�����ӵ��ñ�
local g_callTable = {}
function InitHyperLinkHandler()

	g_callTable[1] = testHyperLink
	g_callTable[2] = confirmCombineFightSoul
	g_callTable[3] = FSEnableAdvance
	g_callTable[4] = FSAutoCombine
	g_callTable[5] = DomainAdvanceLove
	--g_callTable[6] = DomainPlayMaid
	g_callTable[7] = addPlayerTowerResetCount
	g_callTable[8] = luaBuyArenaCount
	g_callTable[9] = confirmBuyPhyStrength
	g_callTable[10] = confirmGoldAddSilverResSpeed
	g_callTable[11] = confirmGoldAddHeroExpResSpeed 
	g_callTable[12] = confirmGoldAddWuHunDianLevelUpSpeed
	g_callTable[13] = confirmGoldAddTieJiangPuLevelUpSpeed
	g_callTable[14] = confirmGoldRefreshHonorConvet
	g_callTable[15] = confirmGoldResetCD
	g_callTable[16] = confirmManorResHarvest
	g_callTable[17] = confirmManorNoCanLootActorReturn
	g_callTable[18] = confirmContributeShopRefresh
	g_callTable[19] = confirmLeaveLegion
	g_callTable[20] = confirmNormalShopRefresh
	--[[g_callTable[1]  = GetEquipDescByContainerPos;
	g_callTable[2]  = HyperLinkWarp2Dungeon;--��ռ��������
	g_callTable[3]  = HyperLinkWarp2NPC;--��ռ��������
	g_callTable[4]  = GetDetailsByObjectID;
	g_callTable[5]  = HyperLinkWarp2Arena;--��ռ��������
	g_callTable[6]  = HyperLinkGetRoleInfo;--ͨ������ID,Account,rolePos�鿴������ɫ����
	g_callTable[7]  = HyperLinkWarp2Refine;--��ռ��������
	g_callTable[8]  = HyperLinkWarp2Forge;--��ռ��������
	g_callTable[9]  = HyperLinkWarp2YanWu;--��ռ��������
	g_callTable[10] = HyperLinkGetRoleSimpleInfo;--ͨ������ID,Account,rolePos�鿴������ɫ����Ϣ
	g_callTable[11] = HyperLinkGetOnlineRoleInfoByEntityID;--ͨ�����ߵĽ�ɫ���鿴������ɫ����
	g_callTable[12] = HyperLinkGetOnlineRoleSimInfoByEntityID;--ͨ�����ߵĽ�ɫ���鿴������ɫ����Ϣ
	g_callTable[13] = HyperLinkGetPetInfo;--ͨ������ID,Account,rolePos,����baseid�鿴������ɫ����
	g_callTable[14] = HyperLinkGetOnlinePetInfoByEntityID;--ͨ�����ߵĽ�ɫ���鿴������ɫ�ĳ�������
	g_callTable[15] = HyperLinkWarp2WorldChat;--��ռ��������
	g_callTable[16] = HyperLinkWarp2NearbyFrinedRecommond;--��ռ��������
	g_callTable[17] = HyperLinkWarp2MagicGhostOpenFunc;--��ռ��������
	g_callTable[18] = HyperLinkWarp2ItemTraceDungeon;--��ռ�������ֲ���׷�ٵ��ؿ�ѡ�����	
	g_callTable[19] = HyperLinkWarp2Bag;--��ռ��������
	g_callTable[20] = HyperLinkWarp2ShouHun;--��ռ��������
	
	g_callTable[21] = HyperLinkGetByNameRoleSimpleInfo;--ͨ����ɫ����ȡ������ɫ������	
	g_callTable[22] = HyperLinkGetByNameRoleInfo;--ͨ����ɫ����ȡ������ɫ��ϸ����
	g_callTable[23] = HyperLinkGetByNamePetInfo;--ͨ����ɫ��������λ�û�ȡ������ɫ��һֻ���������
	
	g_callTable[24] = HyperLinkDrillingGoBack; -- ��ռλ֪ͨ�ͻ�����ת�ص���ǰ���֮ս��
	g_callTable[25] = HyperLinkDrillingRefresh;-- ��ռλ���ͻ�������ʵ�ֵ��ˢ�°�ť
	g_callTable[26] = HyperLinkChanllengMonster; -- ��ս�����ù���
	g_callTable[27] = HyperLinkHoldEmpty; -- ռ��չؿ�
	g_callTable[28] = HyperLinkChallengeHold; -- PVPռ����ս--]]
	
	
	--����������ִ�С����<100,>=100Ϊ�ͻ�������ʹ��
end

function doHyperLinkCall(callInfo)	
	local iFunName = tonumber(callInfo.funname)
	local fun = g_callTable[iFunName];
	if nil == fun then
			LogMsg("no function "..tostring(callInfo.funname) )
			print("no function "..tostring(callInfo.funname) )
			fun = commonCall
	end
	
	fun(callInfo);
end


function HyperLinkError(msg)
	LogMsg("LuaScriptError", msg);
end

function HyperLinkTrace(msg)
	LogMsg("LuaScriptError", msg);
end

function OnHyperLinkMessage(player, args)
	local command = args.context:getString("msg", "");
	command=command..";"
	local resultCallInfo = parseCallInfo(command)
	if resultCallInfo == nil then
		ErrorMsg("Parse Command:["..command.."]Fail")
		return
	end
		
	table.insert(resultCallInfo.paramTb, 1, player)
	doHyperLinkCall(resultCallInfo)
end
