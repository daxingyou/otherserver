#ifndef __CSV_IMP_H__
#define __CSV_IMP_H__

#include "Stream/CsvFile.h"

BEGIN_MINIAPR_NAMESPACE
class CsvImpApr:public CsvImpInterface
{
public:
	friend class TableImp;
	enum
	{
		en_CsvState_Begin = 0,		// ��ʼ״̬
		en_CsvState_Comment,		// ע��״̬
		en_CsvState_Include,		// Include״̬
		en_CsvState_FieldName,		// ��ȡ�ֶ�����
		en_CsvState_FieldDef,		// �ֶζ���Ľ׶�
		en_CsvState_DataReading,	// CSV���ݶ�ȡ
	};
	

	CsvImpApr();
	virtual bool open(const char* strFileName);
	virtual string getFileName();
	virtual Int32 getRecordCount();
	virtual Int32 getFieldCount();
	virtual std::string getString(Int32 row, Int32 nFiled, const char* strDefault="");
	virtual Int32 getInt(Int32 row, Int32 nField, Int32 nDef = 0);
	virtual float getFloat(Int32 row, Int32 nField, float fDef = 0.0);
	virtual void saveToDBC(const char* pszDbcFile, const char* strIndexName);

	virtual void setIndexField(const std::string& strFieldName);
	virtual string getIndexFieldName();
	virtual Int32 findRecord(Int32 nIndexValue);
	virtual std::string getFieldName(Int32 nField);
	Int32 getFieldType(int nFiledIndex);
	virtual Int32 getFieldIndex(const std::string& strFieldName);

	virtual ~CsvImpApr();

private:

	void parseContent(char* pszData, bool bEof);

	
	// ��������
	bool parseDef(const std::string& strRowData);
	
	// ������������
	bool parseFieldNameDef(const std::string& strRowData);

	// ���������Ͷ���
	bool parseFieldTypeDef(const std::string& strRowData);

	// ��������
	bool parseRowData(const std::string& strRowData, bool bEof);

	bool parseCsvData(const string& strCsvData, size_t& beginPos, vector<vector<string> >& orgRowList);

	void fillCsvData(vector<vector<string> >& orgRowList);

	struct CsvItem
	{
		Int8		csvItemType;
		std::string	strItemData;
	};

	struct CsvField
	{
		Int8	csvItemType;
		std::string	strFieldName;
		int iIndex;
	};

	typedef std::vector<CsvItem>				CsvRow;
	typedef std::vector<CsvRow>					CsvData;
	typedef std::map<std::string, std::string>	MacroDef;	
	typedef std::vector<CsvField>				CsvFieldSet;
	typedef std::map<Int32, Int32>				MapIndex;

	CsvData		m_csvData;
	MacroDef	m_macroMap;
	CsvFieldSet	m_fieldData;
	MapIndex	m_indexMap;
	std::map<string, CsvField> m_fieldMap;

	Int8		m_parseState;
	string		m_strFileName;
    string      m_strIndexFieldName;
};

END_MINIAPR_NAMESPACE

#endif
