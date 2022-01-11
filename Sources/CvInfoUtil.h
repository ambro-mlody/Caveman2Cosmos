#pragma once

#ifndef CvInfoUtil_h__
#define CvInfoUtil_h__

#include "CvGameCoreDLL.h"
#include "CvGlobals.h"
#include "CvPython.h"
#include "CvXMLLoadUtility.h"
#include "CheckSum.h"
#include "IDValueMap.h"

struct WrappedVar;


struct CvInfoUtil
	: private bst::noncopyable
{
	CvInfoUtil(const CvInfoBase* info)
	{
		const_cast<CvInfoBase*>(info)->getDataMembers(*this);
	}

	~CvInfoUtil()
	{
		foreach_(const WrappedVar* wrapper, m_wrappedVars)
			delete wrapper;
		m_wrappedVars.clear();
	}

	void initDataMembers()
	{
		foreach_(WrappedVar* wrapper, m_wrappedVars)
			wrapper->initVar();
	}

	void uninitDataMembers()
	{
		foreach_(WrappedVar* wrapper, m_wrappedVars)
			wrapper->uninitVar();
	}

	void readXml(CvXMLLoadUtility* pXML)
	{
		foreach_(WrappedVar* wrapper, m_wrappedVars)
			wrapper->readXml(pXML);
	}

	void copyNonDefaults(const CvInfoUtil otherUtil)
	{
		for (uint32_t i = 0, num = m_wrappedVars.size(); i < num; i++)
			m_wrappedVars[i]->copyNonDefaults(otherUtil.m_wrappedVars[i]);
	}

	void checkSum(uint32_t& iSum) const
	{
		foreach_(const WrappedVar* wrapper, m_wrappedVars)
			wrapper->checkSum(iSum);
	}

	void sendDataMembersToPython(const std::string file) const
	{
		foreach_(const WrappedVar* wrapper, m_wrappedVars)
			wrapper->sendVarToPython(file.c_str());
	}

	static void publishPythonInterface()
	{
		python::class_<CvInfoUtil, boost::noncopyable>("CvInfoUtil", python::init<CvInfoBase*>())
			.def("sendDataMembersToPython", &CvInfoUtil::sendDataMembersToPython)
		;
	}

	///=============================
	/// Variable wrapper base class
	///=============================

	struct WrappedVar : bst::noncopyable
	{
		friend struct CvInfoUtil;

	protected:
		WrappedVar(void* var, const wchar_t* tag)
			: m_ptr(var)
			, m_tag(tag)
		{}

		virtual ~WrappedVar() {}

		virtual void initVar() {}
		virtual void uninitVar() {}
		//virtual void copyVar() {}

		//virtual void read(FDataStreamBase*) {}
		//virtual void write(FDataStreamBase*) {}

		virtual void readXml(CvXMLLoadUtility*) = 0;
		virtual void copyNonDefaults(const WrappedVar*)	= 0;
		virtual void checkSum(uint32_t&) const = 0;

		virtual void sendVarToPython(const char*) const {}

		void* m_ptr;
		const std::wstring m_tag;
	};

	///=================
	/// Integer wrapper
	///=================

	template <typename T>
	struct IntWrapper : WrappedVar
	{
		friend CvInfoUtil;

	protected:
		IntWrapper(T& var, const wchar_t* tag, T defaultValue)
			: WrappedVar(static_cast<void*>(&var), tag)
			, m_default(defaultValue)
		{}

		void initVar()
		{
			ref() = m_default;
		}

		void readXml(CvXMLLoadUtility* pXML)
		{
			pXML->GetOptionalChildXmlValByName(&ref(), m_tag.c_str());
		}

		void copyNonDefaults(const WrappedVar* source)
		{
			if (ref() == m_default)
				ref() = static_cast<const IntWrapper*>(source)->ref();
		}

		void checkSum(uint32_t& iSum) const
		{
			CheckSum(iSum, ref());
		}

		void sendVarToPython(const char* file) const
		{
			Cy::call(file, "handleInteger", Cy::Args()
				<< ref()
			);
		}

		T& ref() const { return *static_cast<T*>(m_ptr); }

	private:
		const T m_default;
	};

	CvInfoUtil& add(int& var, const wchar_t* tag, int defaultValue = 0)
	{
		m_wrappedVars.push_back(new IntWrapper<int>(var, tag, defaultValue));
		return *this;
	}

	CvInfoUtil& add(bool& var, const wchar_t* tag, bool defaultValue = false)
	{
		m_wrappedVars.push_back(new IntWrapper<bool>(var, tag, defaultValue));
		return *this;
	}

	///==============
	/// Enum wrapper
	///==============

	template <typename Enum_t>
	struct EnumWrapper : WrappedVar
	{
		friend CvInfoUtil;

	protected:
		EnumWrapper(Enum_t& var, const wchar_t* tag)
			: WrappedVar(static_cast<void*>(&var), tag)
		{}

		void initVar()
		{
			ref() = static_cast<Enum_t>(-1);
		}

		void readXml(CvXMLLoadUtility* pXML)
		{
			if (pXML->TryMoveToXmlFirstChild(m_tag.c_str()))
			{
				CvString szTextVal;
				pXML->GetXmlVal(szTextVal);
				ref() = static_cast<Enum_t>(GC.getInfoTypeForString(szTextVal));
				pXML->MoveToXmlParent();
			}
		}

		void copyNonDefaults(const WrappedVar* source)
		{
			if (ref() == -1)
				ref() = static_cast<const EnumWrapper*>(source)->ref();
		}

		void checkSum(uint32_t& iSum) const
		{
			CheckSum(iSum, ref());
		}

		void sendVarToPython(const char* file) const
		{
			Cy::call(file, "handleEnum", Cy::Args()
				<< static_cast<int>(ref())
			);
		}

		Enum_t& ref() const { return *static_cast<Enum_t*>(m_ptr); }
	};

	template <typename Enum_t>
	CvInfoUtil& addEnum(Enum_t& var, const wchar_t* tag)
	{
		m_wrappedVars.push_back(new EnumWrapper<Enum_t>(var, tag));
		return *this;
	}

	///================
	/// String wrapper
	///================

	struct StringWrapper : WrappedVar
	{
		friend CvInfoUtil;

	protected:
		StringWrapper(CvString& var, const wchar_t* tag)
			: WrappedVar(static_cast<void*>(&var), tag)
		{}

		void readXml(CvXMLLoadUtility* pXML)
		{
			pXML->GetOptionalChildXmlValByName(ref(), m_tag.c_str());
		}

		void copyNonDefaults(const WrappedVar* source)
		{
			if (ref().empty() || ref() == CvString::format("").c_str())
				ref() = static_cast<const StringWrapper*>(source)->ref();
		}

		void checkSum(uint32_t&) const
		{
		}

		CvString& ref() const { return *static_cast<CvString*>(m_ptr); }
	};

	CvInfoUtil& add(CvString& var, const wchar_t* tag)
	{
		m_wrappedVars.push_back(new StringWrapper(var, tag));
		return *this;
	}

	///================
	/// Vector wrapper
	///================

	template <typename T>
	struct VectorWrapper : WrappedVar
	{
		friend CvInfoUtil;

	protected:
		VectorWrapper(std::vector<T>& var, const wchar_t* tag)
			: WrappedVar(static_cast<void*>(&var), tag)
		{}

		void readXml(CvXMLLoadUtility* pXML)
		{
			pXML->SetOptionalVector(&ref(), m_tag.c_str());
		}

		void copyNonDefaults(const WrappedVar* source)
		{
			foreach_(const T& element, static_cast<const VectorWrapper*>(source)->ref())
				if (element > -1 && algo::none_of_equal(ref(), element))
					ref().push_back(element);
			algo::sort(ref());
		}

		void checkSum(uint32_t& iSum) const
		{
			CheckSumC(iSum, ref());
		}

		void sendVarToPython(const char* /*file*/) const
		{
			//Cy::call(file, "handleVector", Cy::Args()
			//	<< ref()
			//);
		}

		std::vector<T>& ref() const { return *static_cast<std::vector<T>*>(m_ptr); }
	};

	template <typename T>
	CvInfoUtil& add(std::vector<T>& vec, const wchar_t* tag)
	{
		m_wrappedVars.push_back(new VectorWrapper<T>(vec, tag));
		return *this;
	}

	///====================
	/// IDValueMap wrapper
	///====================

	template <typename IDValueMap_T>
	struct IDValueMapWrapper : WrappedVar
	{
		friend CvInfoUtil;

	protected:
		IDValueMapWrapper(IDValueMap_T& var, const wchar_t* tag)
			: WrappedVar(static_cast<void*>(&var), tag)
		{}

		virtual void readXml(CvXMLLoadUtility* pXML)
		{
			ref().read(pXML, m_tag.c_str());
		}

		virtual void copyNonDefaults(const WrappedVar* source)
		{
			ref().copyNonDefaults(static_cast<const IDValueMapWrapper*>(source)->ref());
		}

		void checkSum(uint32_t& iSum) const
		{
			CheckSumC(iSum, ref());
		}

		virtual IDValueMap_T& ref() const { return *static_cast<IDValueMap_T*>(m_ptr); }
	};

	template <typename T1, typename T2, T2 default_>
	CvInfoUtil& add(IDValueMap<T1, T2, default_>& map, const wchar_t* tag)
	{
		m_wrappedVars.push_back(new IDValueMapWrapper<IDValueMap<T1, T2, default_> >(map, tag));
		return *this;
	}

	///============================================
	/// IDValueMap with delayed resolution wrapper
	///============================================

	template <typename IDValueMap_T>
	struct IDValueMapWithDelayedResolutionWrapper : IDValueMapWrapper<IDValueMap_T>
	{
		friend CvInfoUtil;

	protected:
		IDValueMapWithDelayedResolutionWrapper(IDValueMap_T& var, const wchar_t* tag)
			: IDValueMapWrapper<IDValueMap_T>(var, tag)
		{}

		void uninitVar()
		{
			ref().removeDelayedResolution();
		}

		void readXml(CvXMLLoadUtility* pXML)
		{
			ref().readWithDelayedResolution(pXML, m_tag.c_str());
		}

		void copyNonDefaults(const WrappedVar* source)
		{
			ref().copyNonDefaultDelayedResolution(static_cast<const IDValueMapWithDelayedResolutionWrapper*>(source)->ref());
		}
	};

	template <typename T1, typename T2, T2 default_>
	CvInfoUtil& addDelayedResolution(IDValueMap<T1, T2, default_>& map, const wchar_t* rootTag)
	{
		m_wrappedVars.push_back(new IDValueMapWithDelayedResolutionWrapper<IDValueMap<T1, T2, default_> >(map, rootTag));
		return *this;
	}

	///=====================================
	/// IDValueMap of paired arrays wrapper
	///=====================================

	template <typename IDValueMap_T>
	struct IDValueMapOfPairedArrayWrapper : IDValueMapWrapper<IDValueMap_T>
	{
		friend CvInfoUtil;

	protected:
		IDValueMapOfPairedArrayWrapper(IDValueMap_T& var, const wchar_t* rootTag, const wchar_t* firstChildTag, const wchar_t* secondChildTag)
			: IDValueMapWrapper<IDValueMap_T>(var, rootTag)
			, m_firstChildTag(firstChildTag)
			, m_secondChildTag(secondChildTag)
		{}

		void readXml(CvXMLLoadUtility* pXML)
		{
			ref().readPairedArrays(pXML, m_tag.c_str(), m_firstChildTag.c_str(), m_secondChildTag.c_str());
		}

		void copyNonDefaults(const WrappedVar* source)
		{
			ref().copyNonDefaultPairedArrays(static_cast<const IDValueMapOfPairedArrayWrapper*>(source)->ref());
		}

	private:
		const std::wstring m_firstChildTag;
		const std::wstring m_secondChildTag;
	};

	template <typename T1, typename T2, T2 default_>
	CvInfoUtil& add(IDValueMap<T1, T2, default_>& map, const wchar_t* rootTag, const wchar_t* firstChildTag, const wchar_t* secondChildTag)
	{
		m_wrappedVars.push_back(new IDValueMapOfPairedArrayWrapper<IDValueMap<T1, T2, default_> >(map, rootTag, firstChildTag, secondChildTag));
		return *this;
	}

	///========================================================
	/// Wrapped pointers to the data members of an info object
	///========================================================

private:
	std::vector<WrappedVar*> m_wrappedVars;
};

#endif