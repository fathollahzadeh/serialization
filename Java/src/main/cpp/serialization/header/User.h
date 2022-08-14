#ifndef User_H
#define User_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "MediaEntity.h"
#include "URLEntity.h"

using namespace std;

class User : public RootData {

public:
	long id;
	string name;
	string screenName;
	string location;//nullable
	string url;//nullable
	string description;//nullable
	bool isProtected;
	bool isVerified;
	int followersCount;
	int friendsCount;
	int listedCount;
	int favouritesCount;
	int statusesCount;
	string createdAt;
	string profileBannerImageUrl;
	string profileImageUrlHttps;
	bool isDefaultProfile;
	vector <string> withheldInCountries;
	string withheldScope;

	//No longer supported (deprecated) attributes
	vector<URLEntity *> descriptionURLEntities;
	bool isGeoEnabled;
	string lang;
	bool isContributorsEnabled;
	string profileBackgroundColor;
	string profileBackgroundImageUrl;
	string profileBackgroundImageUrlHttps;
	bool profileBackgroundTiled;
	string profileImageUrl;
	string profileLinkColor;
	string profileSidebarBorderColor;
	string profileSidebarFillColor;
	string profileTextColor;
	bool profileUseBackgroundImage;
	bool isDefaultProfileImage;
	int utcOffset;
	string timeZone;
	bool translator;
	bool isFollowRequestSent;
	bool showAllInlineMedia;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		// Simply list all the fields to be serialized/deserialized.
		ar & id;
		ar & name;
		ar & screenName;
		ar & location;
		ar & url;
		ar & description;
		ar & isProtected;
		ar & isVerified;
		ar & followersCount;
		ar & friendsCount;
		ar & listedCount;
		ar & favouritesCount;
		ar & statusesCount;
		ar & createdAt;
		ar & profileBannerImageUrl;
		ar & profileImageUrlHttps;
		ar & isDefaultProfile;
		ar & withheldInCountries;
		ar & withheldScope;

		//No longer supported (deprecated) attributes
		ar & descriptionURLEntities;
		ar & isGeoEnabled;
		ar & lang;
		ar & isContributorsEnabled;
		ar & profileBackgroundColor;
		ar & profileBackgroundImageUrl;
		ar & profileBackgroundImageUrlHttps;
		ar & profileBackgroundTiled;
		ar & profileImageUrl;
		ar & profileLinkColor;
		ar & profileSidebarBorderColor;
		ar & profileSidebarFillColor;
		ar & profileTextColor;
		ar & profileUseBackgroundImage;
		ar & isDefaultProfileImage;
		ar & utcOffset;
		ar & timeZone;
		ar & translator;
		ar & isFollowRequestSent;
		ar & showAllInlineMedia;
	}

public:

	//Default destructor:
	virtual ~User();

	//Default constructor:
	User();

	//Constructor with arguments:
	User(long id, string name, string screenName, string location, string url,
		 string description, bool isProtected, bool isVerified, int followersCount, int friendsCount,
		 int listedCount, int favouritesCount, int statusesCount, string createdAt,
		 string profileBannerImageUrl, string profileImageUrlHttps, bool isDefaultProfile,
		 vector <string> withheldInCountries, string withheldScope,
		 vector<URLEntity *> descriptionURLEntities, bool isGeoEnabled, string lang,
		 bool isContributorsEnabled, string profileBackgroundColor, string profileBackgroundImageUrl,
		 string profileBackgroundImageUrlHttps, bool profileBackgroundTiled, string profileImageUrl,
		 string profileLinkColor, string profileSidebarBorderColor,
		 string profileSidebarFillColor, string profileTextColor, bool profileUseBackgroundImage,
		 bool isDefaultProfileImage, int utcOffset, string timeZone, bool translator, bool isFollowRequestSent,
		 bool showAllInlineMedia);


	//C++: Use explicitly for printing.
	string toJSON();

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	User *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON C++ serialization:
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	User *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(User, boost::serialization::track_never
)

#endif
