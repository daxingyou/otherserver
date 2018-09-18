/*********************************************************
*
*	����: ComponentBase.h
*	����: wuxf
*	ʱ��: 2011-04-17
*	����: ���������
*********************************************************/

#ifndef __COMPONENT_MANAGER_IMP_H__
#define __COMPONENT_MANAGER_IMP_H__

#include "Component/IComponent.h"

BEGIN_MINIAPR_NAMESPACE

class ComponentManagerImp:public IComponentObjectManager
{
public:

	struct schemeInfo
	{
		schemeInfo(){}
		schemeInfo(const schemeInfo& rhs)
		{
			*this = rhs;
		}

		void operator = (const schemeInfo& rhs)
		{
			for(std::map<string, IPropDefine*>::iterator it = mapPropDef.begin(); it != mapPropDef.end(); it++)
			{
				delete it->second;
			}
			mapPropDef.clear();
		
			strName = rhs.strName;
			strDllName = rhs.strDllName;
			strCreateFun = rhs.strCreateFun;
			nVersion = rhs.nVersion;
			dependencyList = rhs.dependencyList;
			propertySet = rhs.propertySet;
		
			for(std::map<string, IPropDefine*>::const_iterator it = rhs.mapPropDef.begin(); it != rhs.mapPropDef.end(); it++)
			{
				string strName = it->first;
				IPropDefine* pNewPropDef = it->second->clone();
				mapPropDef[strName] = pNewPropDef;
			}
		}
		
		~schemeInfo()
		{
			for(std::map<string, IPropDefine*>::iterator it = mapPropDef.begin(); it != mapPropDef.end(); it++)
			{
				delete it->second;
			}
			mapPropDef.clear();
		}
		std::string strName;
		std::string strDllName;
		std::string strCreateFun;
		Int32		nVersion;
		std::vector<std::string>	dependencyList;
		PropertySet propertySet;
		std::map<std::string, IPropDefine*> mapPropDef;
	};
	
	friend class ComponentManager_XmlHandler;

	ComponentManagerImp(){}

	// ��ʱ������Table��ɾ��
	~ComponentManagerImp(){}
	
	virtual IComponent* find(const std::string& strComponentName);

	virtual IObject* createObject(const std::string& strClassName);

	virtual ITable* findTable(const std::string& strTableName);
	
	virtual bool loadScheme(const std::string& strSchemeFile);

	virtual void unLoadAllComponent();

	virtual void _doComponentUnload(IComponent* pComponent);

    //�����¼����������������Ӧ��csv������
    //����ʹ��,��Ҫ�����������:
    //         �����������ͬʱֱ��ʹ�ñ�����,����Ҳ��ʹ�ø��ݱ��������ɵ���֯��������
    //         ��ʱ���ֻ���¼����˱����ݵ�δ������֯�������ݣ����������ݿ��ܵ��³�ͻ
    virtual bool reloadTable(const std::string& strTableName);
    //���ݼ��б��·�����¶�ȡ�����ļ�����һ�ݿ���������������������Ｚ�еı�����
    //���ص�ָ����Ҫ���÷����д����ڴ��ͷ�
	virtual ITable* cloneTableFromStorage(const std::string& strTableName);

	virtual void disableComponent(const string& strComponent);

protected:

	bool initAllComponent();
	IComponent* createComponent(const schemeInfo& componentScheme);
	IComponent* getNextUnloadComponent();
	bool _getComponentName(IComponent* pComponent, std::string& strComponentName);
	bool _removeComponent(const std::string& strComponentName);

private:
	typedef std::map<std::string, IComponent*>	ComponentMap;
	typedef std::map<std::string, schemeInfo>	SchemeMap;
	typedef std::map<std::string, ITable*>	TableMap;
	ComponentMap	m_componentMap;
	SchemeMap		m_componentSchemeMap;
	SchemeMap		m_objectSchemeMap;
	schemeInfo		m_currentScheme;
	TableMap		m_tableMap;

	set<string>		m_disableComponent;
};

END_MINIAPR_NAMESPACE

#endif
