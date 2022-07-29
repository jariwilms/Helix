#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class GUID
	{
	public:
		//Generates a GUID
		//Different generators use different randomizers
		//V1: Time
		//V4: Random
		static GUID generate(const int version = 4)
		{
			switch (version)
			{
				case 1:				return generateV1();
				case 4:				return generateV4();
					
				default:			HLX_CORE_ERROR("GUID version must be between 1 and 4"); return generateV4();
			}
		}

		const std::string toString() const { m_stringFormat; }

		bool operator==(const GUID& other) { return m_guid == other.m_guid; }
		operator std::string() { return m_stringFormat; }

	private:
		explicit GUID(const std::array<byte, 16>& guid)
			: m_guid{ guid }, m_stringFormat{ format() } {}
		explicit GUID(std::array<byte, 16>&& guid)
			: m_guid{ guid }, m_stringFormat{ format() } {}
		
		static GUID generateV1()
		{
			const long long UUID_VERSION = 0x01;
			const long long UUID_VARIANT = 0x08;



			long long timeStamp{};
			short clockSequence{};
			long long nodeId{};

			{
				std::tm tm{};
				std::stringstream ss{ "1582/10/15 00:00:00" };			//4th of October 1582
				ss >> std::get_time(&tm, "%Y/%m/%d %H:%M:%S");
				auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

				auto difference = std::chrono::system_clock::now() - tp;
				timeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count(); //Difference since gregorian calendar in ns

				auto c = clock();
				clockSequence = *(short*)&c;

				nodeId = s_distribution(s_generator);
			}
			
			

			std::array<byte, 16> guid{};

			std::memcpy(&guid[0], &timeStamp, sizeof(long long));
			std::memcpy(&guid[8], &clockSequence, sizeof(byte) * 2);
			std::memcpy(&guid[10], &nodeId, sizeof(byte) * 6);

			auto& version = guid[6];										//Set version => 7th byte ltr
			version &= 0x0F;
			version |= UUID_VERSION << 4;

			auto& variant = guid[8];										//Set variant => 9th byte ltr
			variant &= 0x3F;
			variant |= UUID_VARIANT;

			

			return GUID(std::move(guid));
		}
		static GUID generateV4()
		{
			const long long UUID_VERSION = 0x04;
			const long long UUID_VARIANT = 0x08;


			
			std::array<byte, 16> guid{};

			auto low64 = s_distribution(s_generator);
			auto high64 = s_distribution(s_generator);

			std::memcpy(&guid[0], &low64, sizeof(long long));			//Copy low 64 bits to the guid
			std::memcpy(&guid[8], &high64, sizeof(long long));			//Copy high 64 bits to the guid
			
			auto& version = guid[6];										//Set version => 7th byte ltr
			version &= 0x0F;
			version |= UUID_VERSION << 4;
			
			auto& variant = guid[8];										//Set variant => 9th byte ltr
			variant &= 0x3F;
			variant |= UUID_VARIANT;


			
			return GUID(std::move(guid));
		}
		
		std::string format() const
		{
			unsigned int insertIndex{};
			constexpr int hyphens[] = { 8, 4, 4, 4 };											//Place a hyphen after x amount of hex digits

			std::stringstream ss{};
			for (int i{}; i < 16; ++i)
				ss << std::hex << std::setfill('0') << std::setw(2) << (int)m_guid[i];			

			std::string guid{ss.str()};
			for (const auto& hyphen : hyphens)
			{
				insertIndex += hyphen;
				guid.insert(insertIndex, "-");
				++insertIndex;
			}

			guid.insert(0, "{");
			guid.append("}");

			return guid;
		}

		static inline std::chrono::high_resolution_clock s_clock;
		
		static inline std::random_device s_device;
		static inline std::mt19937_64 s_generator{ s_device()};
		static inline std::uniform_int_distribution<long long> s_distribution{ 0, std::numeric_limits<long long>::max() };

		const std::array<byte, 16> m_guid;
		const std::string m_stringFormat;
	};
}
