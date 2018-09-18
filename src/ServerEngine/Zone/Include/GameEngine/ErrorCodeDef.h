#ifndef __ERROR_CODEDEF_H__
#define __ERROR_CODEDEF_H__

enum
{
	ERROR_SYSERROR = 1,                // ϵͳ����
	ERROR_GETROLE_ERROR = 2,			// ��ȡ��ɫ��Ϣ����
	ERROR_DUNPLICATENAME = 3,		    // ��ɫ��������
	ERROR_NEWROLE_SYSERROR = 4,      // �½���ɫϵͳ����
	ERROR_ROLENAME_EMPTY = 5,        // ��ɫ����Ϊ��
	ERROR_ROLENAME_TOOLONG = 6,      // ��ɫ����̫����
	ERROR_DUNGEON_SECTION_NOTOPEN = 7, // �½�δ����
	ERROR_NEED_PHYSTRENGTH = 8,// ��������
	ERROR_SECTION_GETED = 9,  // �½�����ͨ�ؽ����Ѿ���ȡ��
	ERROR_NOT_ONFORMATION = 10, // ����������
	ERROR_FORMATION_SAMEID = 11, // �������Ѿ�����ͬ��Ӣ����
	ERROR_FORMATION_LIMIT = 12, // �ﵽ��������������
	ERROR_FIGHTSOUL_BAGFULL = 13, // ��걳������F=
	ERROR_NEED_SILVER = 14,      // ���Ҳ���
	ERROR_EXIST_SAMEID_FIGHTSOUL = 15, // �Ѿ�װ������ͬ�������
	ERROR_FIGHTSOUL_LOCKED = 16, // ����Ѿ�������
	ERROR_NOVALID_FIGHTSOL = 17, // û�п��Ժϲ������
	ERROR_FIGHTSOUL_TOUCHMAX = 18, // �Ѿ��ﵽ������
	ERROR_NEED_CHIP = 19, //�����Ƭ����
	ERROR_TOUCH_MAXHERO = 20, // �ﵽӢ��������
	ERROR_NEED_ITEM = 21, // ��Ʒ����
	ERROR_HERO_TOUCHMAXLV = 22, // Ӣ�۴ﵽ��ߵȼ���
	ERROR_NO_HEROEXP = 23, // ��Ϊ����
	ERROR_HERO_CAONNOTINFORMATION = 24, // Ӣ�۲���������
	ERROR_HERO_NEEDSAMEID = 25, // ������ͬ��Ӣ��
	ERROR_HERO_TOULEVELSTEPLIMIT = 26, // Ӣ�۵Ƚ״ﵽ���
	ERROR_ITEM_CANNOTUSE = 27, // ��Ʒ����ʹ��
	ERROR_GODANIMAL_SAMEID = 28, // �Ѿ�������ͬ��������
	ERROR_GODANIMAL_MAXLEVEL = 29, // ���޴ﵽ���ȼ���
	ERROR_GODANIMAL_NEEDLEVELSTEP = 30, //  �Ѿ��ﵽ��ǰ�Ƚ׵����ȼ���
	ERROR_GODANIMAL_MAXLEVELSTEP = 31, //�Ѵ���ߵȽ�
	ERROR_NEED_GOLD = 32, // Ԫ������
	ERROR_GODANIMAL_INVALID_INHERIT = 33, // �����߱���ȼ����ߵȽױȱ������߸�
	ERROR_FORMATION_CANNOTEMPTY = 34, // ������������Ҫ��һ����
	ERROR_DOMAIN_LOVELIMIT = 35, // ���Ҵ����ﵽ����
	ERROR_DOMAIN_LOVECD = 36, // ����CD
	ERROR_DOMAIN_PLAYED = 37, // �Ѿ���Ϸ��
	ERROR_DOMAIN_GOLDMINELIMIT = 38, // ��������������
	ERROR_DOMAIN_MONSTERDEAD = 39, // ��Դ�����Ѿ�����
	ERROR_DOMAIN_LOOTCD = 40, // �Ӷ�CD
	ERROR_DOMAIN_LOOTPROTECT = 41, // �Ӷᱣ����
	ERROR_FUNCTION_NOTOPEN =42, // δ�����ù���
	ERROR_DOMAIN_BEPLAYLIMIT = 43, // ����Ϸ����
	ERROR_DOMAIN_NOTOPEN = 44, // �Է����δ����
	ERROR_LEGIONNAME_EXIST = 45, // ������������

	ERROR_LEGION_NOREADY = 46, // ������δ׼����
	ERROR_LEGION_NAMETOOLONG = 47, // ��������̫��
	ERROR_RCV_NOTONLINE = 48, // Ŀ�겻����
	ERROR_HAS_LEGION = 49, // �Ѿ��о�����
	ERROR_HAS_APPLYED = 50, // �Ѿ�������
	ERROR_APPLY_FULL = 51, // ���������Ѿ�����
	ERROR_NO_RIGHT = 52, // û��Ȩ��
	ERROR_TARGET_NOT_MEMBER = 53, // Ŀ�겻�Ǿ��ų�Ա
	ERROR_CANNOT_KICKSELF = 54,//�������Լ�
	ERROR_LEGION_BLESSED = 55, // �Ѿ�ף������
	ERROR_LEGION_PAYGETED = 56, // ���Ÿ����Ѿ���ȡ
	ERROR_NO_CONTRIBUTE = 57, // ���ײ���
	ERROR_LEADER_CONNOTLEAVE = 58, // �ų���������
	ERROR_NO_APPLYED = 59, // δ����
	ERROR_ONLY_LEADER = 60, // ֻ���ų��ܽ��иò���
	ERROR_CALLBOSS_CD = 61, // ��ʱ�������ٻ�BOSS
	ERROR_CUR_ALIVE = 62, // ��ǰ��������״̬
	ERROR_CUR_NOLEGIONBOSS = 63, // ��ǰû�о���BOSS
	ERROR_BOSS_ISRUNNING = 64, // ����BOSS�Ѿ�����
	ERROR_LEGION_MAXLEVEL = 65, // ���ŵȼ��ﵽ����
	ERROR_LEGION_FIGHTING = 66, // ����ս���в��ܲ鿴
	
	ERROR_IN_TOWERTOP = 70, //��ͨ������߲�
	ERROR_IN_BOTTOM = 71,   //��ײ㲻������
	ERROR_LACK_RESETCOUNT = 72, //���ô�������
	ERROR_NO_REPORTRIGHT = 73, // û����սȨ��
	ERROR_IN_LEGIONFIGHTING = 74, // ����ս����
	ERROR_REPORTED_OTHERCITY = 75, // �Ѿ���������������
	ERROR_NO_REPORTCITY = 76, // û����ս����
	ERROR_JOINED_CITY = 77, // �Ѿ�������ս��
	ERROR_REPORT_LEVEL = 78, // ���Ų��������ȼ�
	ERROR_REPORT_FULL = 79, // ����ص���ս��������
	ERROR_LEGIONSHOP_USED = 80, // �̵��λ���Ѿ���������
	ERROR_LEGIONFIGHT_LEVEL = 81, // ���ŵȼ�������������ս
	ERROR_LEGIONFIGHT_NOSTART = 82, // �������ս��δ����
	ERROR_LEGION_INFIGHTING = 83, // �������ս�У��������ɢ
	ERROR_NO_GIFT = 84, // �������������
	
	ERROR_LEGIONBOSS_TOUCHMAX = 85, // ����ﵽ����

	ERROR_ARENA_BUYLIMIT = 86, // ��������������ﵽ����
	ERROR_ARENA_BUSY = 87, //ϵͳ��æ


	ERROR_NO_HONOR = 88,         //�����㲻��
	ERROR_ADD_ITEM = 89,         //��ӵ���ʧ��
	ERROR_CANBUY_TIMES = 90, //�Ѵﹺ�����޲��ܼ�������
	ERROR_ARENA_NEEDCOUNT = 91, // �����������Ѿ�����
	ERROR_PVE_CD = 92, // PVE��ȴ��
	ERROR_WORLDBOSS_CHEERLIMIT = 93, // ����BOSS �����������
	ERROR_LEGIONBOSS_CD = 94, // ����BOSSCD
	ERROR_WORLDBOSS_CD = 95, // ����BOSSCD
	ERROR_WORLDBOSS_ALIVE = 96, // ���״̬�����踴��
	
	ERROR_CAMPBATTLE_NOTACTIVE = 97, //��Ӫսδ�ﵽ����ʱ��
	ERROR_BUYPHYSTRENGTHLIMIT = 98, // �������������ﵽ����
	ERROR_CAMPBATTLE_SIGNOUT = 99,	//�˳�����
	ERROR_CAMPBATTLE_SIGNIN = 100,	//��Ӫս�������
	ERROR_ACTORNAME_NOEXITED = 101, //�û�������
	ERROR_HAS_FRIEND = 102,			//�Ѿ���������
	ERROR_OVER_GIVELIMIT= 103,     //��������������
	ERROR_OVER_GETLIMITTIMES = 104, //��������ȡ����
	ERROR_HAS_REQUESTLIST  = 105,	//�ȴ��Է����ͬ��
	
	ERROR_DUNGEON_NOPERFECT = 106, // ����ͨ�ز�����ȡ����
	ERROR_FIGHTSOUL_ADVANCELIMIT = 107,  // ����Ӧ���ٻ������Ѿ�����
	ERROR_FRIENDSYSTEM_HAVE_GETSTRENGTH = 108,//�Ѿ���ȡ��������ֵ
	ERROR_FRIENDSYSTEM_HAVE_GIVESTRENGTH = 109,//�Ѿ�����������ֵ
	ERROR_FRIENDSYSTEM_NOT_FRIEND = 110, //�Ѿ���������
	ERROR_NOTIN_LEGIONCHAT = 111, // δ������ţ����ܾ�������

	ERROR_DOMAIN_PLAYLIMIT = 112, // ��Ϸ��������

	ERROR_DOMAIN_NOOPEN = 113, // ���δ����
	ERROR_LEGION_NOOPEN = 114, // ����δ����


	
	ERROR_SHOPHEROGUIDE_NOOPEN = 122, // �̳ǳ�ȡӢ�۹���δ����
	ERROR_GODANIMAL_NOOPEN = 123, // ����δ����
	ERROR_ARENA_NOOPEN = 124, // ������δ����
	ERROR_FRIEND_NOOPEN = 125, // ����δ����
	ERROR_WORLDBOSS_NOOPEN = 126, // ����BOSSδ����
	ERROR_FIGHTSOUL_NOOPEN = 127, // ���δ����
	ERROR_CAMP_NOOPEN = 128, // ��Ӫսδ����
	ERROR_CLIMTOWER_NOOPEN = 129, // ����δ����
	ERROR_CLiMTOWER_HAVENOT_PAST = 130,  //��������������ͨ���Ĳ�
	ERROR_CLIMTOWER_RESETCOUNT_OVERFLOW = 131, //���ô�����������������

	ERROR_LEGIONAME_INVALID = 132, // �������ַǷ�
	ERROR_ROLENAME_INVALID = 133, // ���ֺ��зǷ��ַ�
	ERROR_CLIMBTOWER_NOBUYTIMES = 134, //ͨ�������չ�������Ѿ�����

	ERROR_GODANIML_ACTIVE_NOITEM = 135, //����������Ʒ����

	ERROR_HERO_CONVERT_NOOPEN = 136, // �ֻع�����δ����
	ERROR_HERO_CANNOTSANGO_FIGHTSOUL = 137, // �ѵ����ϵ��������ɢ��

	
	ERROR_CANNOTQUIT_FIRSTSCENE = 138, // ��һ�ز����˳�
	ERROR_SHOP_NOOPEN = 139,				//�̳�δ����
	ERROR_HEROLEVEL_3ACTORLEVEL = 140, // ���������ǰ��Ӣ�۵ȼ����ܳ�����ҵȼ�X3

	ERROR_GODANIMALLEVEL_3ACTORLEVEL = 141, // ���������ǰ�����޵ȼ����ܳ�����ҵȼ�X3

	ERROR_EQUIPPOS_INVALID = 145, // װ��λ�ò���
	ERROR_INVALID_EQUIP = 146, // ���Ϸ���װ��
	ERROR_EQUIP_LEVEL = 147, // δ�ﵽװ���ȼ�
	ERROR_EQUIPBAG_FULL = 148, // װ����������
	ERROR_EQUIP_CANNOTSELL = 149, // ���װ�����ܳ���

	ERROR_CANNOT_QUERYGODMINE = 150, // �����ܼ��ٽ�����

	ERROR_CANNOTSANGO_EQUIP = 151, // �ѵ����ϵ�װ�������ɢ��

	ERROR_HAVEEQUIPORSOUL_CANNOT_SELL = 152, //��װ������겻�ܳ���
	
	ERROR_EQUIP_MAXLEVEL = 153, // װ���ﵽ��ߵ�
	ERROR_EQUIP_MASTERLV_LIMIT = 154, // װ���ȼ��ﵽ����2����

	ERROR_DUNGEON_COUNTLIMIT = 155, // FB��ս��������

	ERROR_CANNOTSAODANG_STAR3 = 156, // ֻ��3��ͨ�صĹؿ�����ɨ��

	ERROR_SAODANG_NOPOINT = 157, // ��ǰɨ����������

	ERROR_MAIL_NOTEXIST = 158, // �ʼ�������

	ERROR_MAIL_NOAWARD = 159, // û�и���

	ERROR_MAIL_AWARDED = 160, // �����Ѿ�����ȡ��

	ERROR_MAIL_AWARDERROR = 161, // �ʼ���������
	
	ERROR_DREAMLAND_CANUPFORAMTION_LIMIT = 162,  //�þ��ɳ�ս�����ﵽ��
	
	ERROR_DREAMLAND_RESETTIEMS_LIMIT = 163,		//�þ����տ����ô����ﵽ����
	
	ERROR_DREAMLAND_NOOPNE = 164, //�þ�δ����
	
	ERROR_DREAMLAND_GREGUARD_ERROR = 165, //�þ���ȡ�عؽ���Ϣʧ��

	ERROR_DREAMLAND_HERO_INFORMATION = 166, //�ڳ�����

	ERROR_DREMALAND_NO_HERO = 167,		//û��Ӣ��

	ERROR_DREAMLAND_ISLOCK_SECTION = 168, //����˷������þ�

	ERROR_HERO_LACKSOUL = 170, // ȱ�ٻ���

	ERORR_TALLENT_NEEDITEM = 171, // �츳ͻ�ƣ�ȱ�ٲ���

	ERROR_TALLENT_NEEDLEVELSTEP = 172, // �츳ͻ�ƣ��Ƚײ���

	ERROR_HERO_MAXLEVELSTEP = 173, // �Ѿ��ﵽ���Ƚ�

	ERROR_MANOR_SILVER_LEVELUPOVER = 174, //���ͭ�������Ѿ����

	ERROR_MANOR_HEROEXP_LEVELUPOVER = 175,	//�����Ϊ�������Ѿ���� 

	ERROR_MANOR_RES_LEVELLIMIT = 176,	//���Ѿ��ﵽ��߼�����������

	ERROR_MANOR_RES_LEVELUPACTOR_THRICE = 177, //��ؿ�ȼ����ܸ������3��

	ERROR_MANOR_RES_HAVESTLIMIT = 178,//��ȡ��ؿ�����Ѵ�����

	ERROR_MANOR_WUHUNDIAN_LEVELIMMIT = 179, //����ﵽ��õȼ���������

	ERROR_MANOR_TIEJIANGPU_LEVELLIMIT = 180, //�����̴ﵽ��õȼ���������

	ERROR_MANOR_LOOT_NOT_THETIME = 181,	//ÿ��8~23��ſ����Ӷ�
	
	ERROR_MANOR_LOOT_VIGOR = 182, //�Ӷ���������

	ERROR_MANOR_LOOT_OTHERBEFORYOU = 183, //��Ҫ�Ӷ�����������Ӷ���

	ERROR_HERO_EXIST = 184, // Ӣ���Ѿ�����

	ERROR_QUALITY_TOUCHMAX = 185,

	ERROR_MANOR_CANLEVELUP_LIMIT = 186,//����������

	ERROR_MANOR_ISLEVELUP = 187,	//���ڴ�����

	ERROR_MANOR_NOT_MORE_BUILDTEAMS = 188,	//û�ж���Ľ�����

	ERROR_CALLHERO_NEEDITEM = 189,

	ERROR_NEED_TOKEN = 190,					//���Ʋ���'

	ERROR_NO_CANLOOTACTOR = 191,				//û�п��Ӷ�����

	ERROR_HEROTALLENT_NEEDMASTERLV = 200, // �����ȼ�����

	ERROR_HEROTALLENT_TOCHMAXLV = 201, // �Ѿ��ﵽ��ߵȼ�

	ERROR_DREAMLAND_HERO_HAVE_DEATH = 202,	//���Ӣ���Ѿ�����
	ERROR_DREAMLAND_DEATH_HERO_LIMIT = 203,	//���������ﵽ����

	ERROR_DUNGON_SAODANG_OPENLEVEL = 204,		//15������ɨ��

	ERROR_ARENA_RESET_ERROR_CD = 205,		//����ʱCD �Ѿ����
	
	ERROR_ARENA_IN_CD = 206,					//��CD ��

	ERROR_MANOR_OPEN_LEVEL = 207,			//����7������

	ERROR_MANOR_TIEMS_LIMIT = 208,			//��������������

	ERROR_MANOR_TOLOOT_OPNELEVEL = 209,		//����ӶṦ�ܿ�ʼ�ȼ�10

	ERROR_CHAT_HAVE_RESERVER = 210,			//���д�

	ERROR_CHAT_MSG_TOOLONG = 211,			//������Ϣ̫��

	ERROR_FRIENDSYSTEM_FRINEDLIMIT = 212,     //���������ﵽ����

	ERROR_MANOR_IN_PROTECT = 213,			//�Ӷ�����ڱ���ʱ��

	ERROR_MANOR_TIEJIANGPU_OPENLEVEL = 214,	//�����̿����ȼ�7��

	ERROR_CONVERTCODE_HAVEUSE = 215,   //�һ��뱻����������

	ERROR_CONVERTCODE_HAVENOT = 216, //û������һ���

	ERROR_CONVERTCODE_ACTORHAVE = 217,	//����Ѿ��һ���������

	ERROR_CANNOT_SAVEMONEY = 218, // δ���ų�ֵ

	ERROR_NAME_BANSTRING = 219, // ����������

	ERROR_ACCOUNT_OTHERLOGIN = 220, // �ʺ���ص�¼

	ERROR_FRIEND_FRIEND_LIMIT = 221,	//���ѵĺ����б�����

	ERROR_FRIEND_FRIEND_LEVEL = 222,	//��Ҫ��ӵĺ��ѵȼ�����

	ERROR_LEGION_WORSHIP_TIMES = 223,	//Ĥ�ݴ����Ѿ�����

	ERROR_LEGION_SHOP_OPENLEVEL = 224,	//�����̵꿪���ȼ�

	ERROR_LEGION_WEEK_APP_TIMES = 225,	//���ſ���������Ѿ�����

	ERROR_LEGION_LEAVE_SECOND = 226,	//�뿪����24Сʱ�ڲ��ܼ���

	ERROR_EQUIP_JOBINVALID = 227,

	ERROR_LEGION_BUILD_TIMES= 228, //���Ž����������

	ERROR_OPERATE_CHECKIN_OVER = 229,	//���տ���ȡ���������꣬����VIP

	ERROR_COMBINE_XIHAO_NEEDITEM = 230, // �ϳ�ϲ��Ʒ���ϲ���

	ERROR_LEGION_VICE_LIMIT = 231, //�����ų���������

	ERROR_LEGION_MEMBER_LIMIT = 232, //��������������
	
	ERROR_FIGHT_TOO_FIGHT = 233,  //ս�����̫��

	ERROR_MONTH_CARD_REMAIND = 234, //�¿�ʣ�����

	ERROR_EQUIP_HASNO_XILIAN_PROP = 235,	// װ��û��ϴ������

	ERROR_EQUIP_XILIAN_LV_LIMIT = 236,	// 40������װ�����칦��

	ERROR_LEGION_NOT_INREPORT = 246,  //���ڱ���ʱ��
	ERROR_HAVE_REPORT = 237,  //ֻ����սһ������
	ERROR_NOTIN_LEGIONCAMPBATTLE = 238, //û����ս����
	ERROR_LEGION_NOTREPORT = 239, //û�вμӾ���ս
	ERROR_ATT_MEM_ISBUSY = 240,  //Ҫս���������æ
	ERROR_ATT_STAR_LOST = 241,  //�ǽ��Ѿ����Ӷ�
	ERROR_LEGION_REPROT_NOMONEY = 242,
	ERROR_RE_REPORT = 243, //��ѡս
	ERROR_REPORT_SELF = 244, //���Լ���ս

	ERROR_LEGION_MEMBER_LIMITE = 245,
	ERROR_LEGION_HAVE_BATTLE = 247,

	ERROR_LEGION_APP_INBATTLE = 248,
	ERROR_LEGION_KICKMEMBER_INBATTLE = 249
};




#endif
