

function testHyperLink(callInfo)
	local player = callInfo.paramTb[1];
	local Account = player:getProperty(PROP_ACTOR_ACCOUNT, "");
	local handle = player:getHandle();
	
	print("-----"..Account.."|"..handle.."|"..callInfo.paramTb[2])
end

function confirmCombineFightSoul(callInfo)
	local player = callInfo.paramTb[1];
	local handle = player:getHandle();
	
	local srcConType = tonumber(callInfo.paramTb[2]);
	local srcPos = tonumber(callInfo.paramTb[3]);
	local dstConType = tonumber(callInfo.paramTb[4]);
	local dstPos = tonumber(callInfo.paramTb[5]);
	local heroObjectID = tonumber(callInfo.paramTb[6]);
	doFightSoulCombine(handle, srcConType, srcPos, dstConType, dstPos, heroObjectID)
end

function makeColorString(strMsg, color)
	if nil == color then
		color = "255 255 255"
	end
	return "<lb cl=\""..color.."\" c=\""..strMsg.."\"/>"
end

function sendFightSoulCmbConfirm(args)
	local entityID = args.context:getInt("entity");
	local srcConType = args.context:getInt("srcConType");
	local srcPos = args.context:getInt("srcPos");
	local dstConType = args.context:getInt("dstConType");
	local dstPos = args.context:getInt("dstPos");
	local heroID = args.context:getInt("heroObjectID");
	
	local srcName = args.context:getString("scrName", "");
	local dstName = args.context:getString("dstName", "");
	local getExp = args.context:getInt("exp");
	local curLevel = args.context:getInt("level");
	local newLevel = args.context:getInt("newlevel");
	
	local expStr = "���"..getExp.."����";
	if curLevel ~= newLevel then
		expStr = expStr.."������"..newLevel.."��"
	end
	
	local msg = ""..dstName..makeColorString("������")..srcName..makeColorString(expStr)
	
	local leftName = "ȡ��"
	local righrName = "ȷ��"
	
	local leftCmd = ""
	local righrCmd = "2#"..srcConType.."#"..srcPos.."#"..dstConType.."#"..dstPos.."#"..heroID;
	
	sendCommDlg(entityID, msg, righrName, righrCmd, leftName, leftCmd)
end

function FSEnableAdvance(callInfo)
	local player = callInfo.paramTb[1];
	local handle = player:getHandle();
	enableFSAdvance(handle)
end


function FSAutoCombine(callInfo)
	local player = callInfo.paramTb[1];
	local handle = player:getHandle();
	autoCombineFightSoul(handle)
end

function NotifyFSEnableAdvance(args)
	local entityID = args.context:getInt("entity");
	local costGold = args.context:getInt("costGold");
	local leftCount = args.context:getInt("leftCount");
	
	local msg = makeColorString("����"..costGold.."Ԫ���ٻ�����Ӧ��״̬?\\n")
	msg = msg..makeColorString("���׻�ø�Ʒ����꣬�����������Ƭ\\n", "0, 255, 0")
	msg = msg..makeColorString("����ʣ���ٻ�����:"..leftCount)
	
	local leftName = "ȡ��"
	local leftCmd = ""
	local rightName = "ȷ��"
	local rightCmd = "3"
	sendCommDlg(entityID, msg, rightName, rightCmd, leftName, leftCmd)
end

function NotifyAutoCombine(args)
	local entityID = args.context:getInt("entity");
	local hostName = args.context:getString("hostName", "");
	local getExp = args.context:getInt("exp");
	
	local curLevel = args.context:getInt("level");
	local newLevel = args.context:getInt("newlevel");
	
	local descStr = "�����ɱ��������������"..getExp.."����"
	if curLevel ~= newLevel then
		descStr = descStr.."������"..newLevel.."��"
	end
	
	local msg = hostName..makeColorString(descStr.."���Ƿ���кϳɣ�")
	local leftName = "ȡ��"
	local leftCmd = ""
	local rightName = "ȷ��"
	local rightCmd = "4"
	
	sendCommDlg(entityID, msg, rightName, rightCmd, leftName, leftCmd)
end

function DomainAdvanceLove(callInfo)
	local player = callInfo.paramTb[1];
	local handle = player:getHandle();
	
	loveMaid(handle, true)
end

--function ConfirmAdvanceLove(args)
	--local entity = args.context:getInt("entity");
	--local neeedGold = args.context:getInt("needGold");
	
	--local msg = "�Ƿ�����"..neeedGold.."Ԫ���߼����ң�"
	--local leftName = "ȡ��"
	--local leftCmd = ""
	--local rightName = "ȷ��"
	--local rightCmd = "5"
	
	--sendCommDlg(entity, msg, rightName, rightCmd, leftName, leftCmd)
--end


--function DomainPlayMaid(callInfo)
	--local player = callInfo.paramTb[1];
	--local handle = player:getHandle();
	--local strAccount = callInfo.paramTb[2];
	--local worldID = tonumber(callInfo.paramTb[3])
	--playMaid(handle, true, strAccount, worldID)
--end

--function ConfirmAdvancePlay(args)
--	local entity = args.context:getInt("entity");
--	local targetAccount = args.context:getString("targetAccount", "");
--	local worldID = args.context:getInt("worldid");
--	local costGold = args.context:getInt("costGold");
	
--	local msg = "ȷ������"..costGold.."Ԫ���߼���Ϸ��"
--	local leftName = "ȡ��"
	--local leftCmd = ""
	--local rightName = "ȷ��"
	--local rightCmd = "6#"..targetAccount.."#"..worldID
	
--	sendCommDlg(entity, msg, rightName, rightCmd, leftName, leftCmd)
--end
function AddTowerRestCount(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("costGold")
	
	local msg = "����"..costGold .."Ԫ������һ�����ô�����"
	local leftName = "ȡ��"
	local leftCmd = "";
	local rightName = "ȷ��"
	local rightCmd = "7"
	sendCommDlg(entity, msg, rightName, rightCmd, leftName, leftCmd)
end
function addPlayerTowerResetCount(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	addTowerResetCount(handle,true)
end


function sendBuyChallengeConfirm(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("needgold")
	
	local msg = "����"..costGold.."Ԫ������5����ս������"
	local leftName = "ȷ��"
	local leftCmd = "8"
	local rightName = "ȡ��"
	local rightCmd = ""
	
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function luaBuyArenaCount(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	
	buyArenaCount(handle);
end


function MakeSysInfo(args)
	local userSize = args.context:getInt("accountsize")
	local actorSize = args.context:getInt("playersize")
	local startTime = args.context:getInt("starttime")
	
	local msg = makeColorString("�ʺ���Ŀ:"..userSize.."\\n")
	msg = msg..makeColorString("�����Ŀ:"..actorSize.."\\n")
	msg = msg..makeColorString("����������ʱ��:"..os.date("%Y-%m-%d %H-%M-%S", startTime) )
	
	return msg
end


function NotiyBuyPhyStrength(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	local getPhy = args.context:getInt("getphy");
	local haveByTimes = args.context:getInt("haveByTimes");
	local msg = "����"..costGold.."Ԫ������"..getPhy.."�������Ƿ������".."(�����ѹ���"..haveByTimes.."��)"
	
	local leftName = "ȷ��"
	local leftCmd = "9"
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmBuyPhyStrength(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	
	buyPhystrength(handle);
end

function ManorSilverGoldAddSpeed(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	local name = args.context:getString("name","")
	local resId = args.context:getInt("resId")
	
	local msg = "����"..costGold.."Ԫ���������"..name.."����"
	
	local leftName = "ȷ��"
	local leftCmd = "10#"..costGold.."#"..resId
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmGoldAddSilverResSpeed(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	local cost = callInfo.paramTb[2]
	local resId = callInfo.paramTb[3]
	manorSilverResGoldAddSpeed(handle,cost,resId)
end

function manorHeroExpGoldAddSpeed(args)
	
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	local name = args.context:getString("name","");
	local resId = args.context:getInt("resId")
	
	local msg = "����"..costGold.."Ԫ���������"..name.."����"
	
	local  leftName = "ȷ��"
	local leftCmd = "11#"..costGold.."#"..resId
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmGoldAddHeroExpResSpeed(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	local cost = callInfo.paramTb[2]
	local resId = callInfo.paramTb[3]
	manorHeroExpResGoldAddSpeed(handle,cost,resId)
end

function manorWuHunDianGoldAddLevelUpSpeed(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	
	local msg = "����"..costGold.."Ԫ������������������"
	
	local leftName = "ȷ��"
	local leftCmd = "12#"..costGold
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmGoldAddWuHunDianLevelUpSpeed(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	local costGold = callInfo.paramTb[2]
	manorGoldAddWuHunDianLevelUpSpeed(handle , costGold)
end

function manorTieJiangPuGoldAddLevelUpSpeed(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	
	local msg = "����"..costGold.."Ԫ��������������̵�����"
	
	local leftName = "ȷ��"
	local leftCmd = "13#"..costGold
	local rightName ="ȡ��" 
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmGoldAddTieJiangPuLevelUpSpeed(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	local costGold = callInfo.paramTb[2]
	manorGoldAddTieJiangPuLevelUpSpeed(handle, costGold)
end

function shopHonerConvertRefreshCost(args)
	print("--- in Hero.lua shopHonerConvertRefreshCost");
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	
	local msg = "�Ƿ񻨷�"..costGold.."������ˢ��"
	
	local leftName = "ȷ��"
	local leftCmd = "14"
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end



function confirmGoldRefreshHonorConvet(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	ShopsytemGoldRefreshHonorConvet(handle)
end

-- ��ͨ�̻���ȷ��
function normalShopRefreshCost(args)
	print("--- in Hero.lua, normalShopRefreshCost");
	local entity = args.context:getInt("entity");
	local cost = args.context:getInt("cost");
	
	local msg = "�Ƿ񻨷�"..cost.."��Ԫ��ˢ��";
	local leftName = "ȷ��";
	local leftCmd = "20";
	local rightName ="ȡ��";
	local rightCmd = "";
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd);
end

-- ȷ�ϻص�
function confirmNormalShopRefresh(callInfo)
	local player = callInfo.paramTb[1];
	local handle = player:getHandle();
	ShopsystemYuanbaoRefreshNormalShop(handle);
end

function arenaGlodResetCD(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	
	local msg = "�Ƿ񻨷�"..costGold.."Ԫ��������սCD"
	
	local leftName = "ȷ��"
	local leftCmd = "15"
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmGoldResetCD(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	confirmArenaGlodResetCD(handle)
end

function manorResHarvest(args)
	local entity = args.context:getInt("entity")
	local remaind = args.context:getInt("remaind")
	
	local msg = makeColorString("���� 1 ����ȡ������ȡ��ǰ������ͭ������Ϊ��\\n")
	msg = msg..makeColorString("��ǰʣ����ȡ����:"..remaind, "0 255 0")
	
	local leftName = "ȷ��"
	local leftCmd = "16"
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmManorResHarvest(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	manorResHarvestReturn(handle)
end

function manorNoCanLootActor(args)
	local entity = args.context:getInt("entity")
	
	local msg = "��ʱû���ҵ������Ӷ�����,����������"
	
	local leftName = "����"
	local leftCmd = "17"
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmManorNoCanLootActorReturn(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	manorNoCanLootActorReturn(handle)
end

function contributeShopRefreshCost(args)
	local entity = args.context:getInt("entity")
	local costGold = args.context:getInt("cost")
	
	local msg = "�Ƿ񻨷�"..costGold.."�㹱��ˢ��"
	
	local leftName = "ȷ��"
	local leftCmd = "18"
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmContributeShopRefresh(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	contributeShopRefreshConfirm(handle)
end

function leaveLegionNotice(args)
	local entity = args.context:getInt("entity")
	local iRemaindTimes = args.context:getInt("remaindTimes")
	
	local msg = makeColorString("�˳���48Сʱ�޷��ص�ԭ����\\n")
	msg = msg..makeColorString("����ʣ��ɼ�����Ŵ�����"..iRemaindTimes, "255 0 0")
	
	local leftName = "ȷ��"
	local leftCmd = "19"
	local rightName = "ȡ��"
	local rightCmd = ""
	sendCommDlg(entity, msg, leftName, leftCmd, rightName, rightCmd)
end

function confirmLeaveLegion(callInfo)
	local player = callInfo.paramTb[1]
	local handle = player:getHandle()
	leaveLegionCallBack(handle)
end


