#ifndef __USER_H__
#define __USER_H__

#include<string>

class User
{
public:
	User(User const&) = delete;
	void operator=(User const&) = delete;

	static User* getInstance()
	{
		static User INSTANCE;
		return &INSTANCE;
	}

	void setID(const std::string& id) { this->id = id; }
	std::string getID()const { return id; }

	void setName(const std::string& name) { this->name = name; }
	std::string getName()const { return name; }

	void setRole(const std::string& role) { this->role = role; }
	std::string getRole()const { return role; }

private:
	User(){}

	std::string id;
	std::string name;
	std::string role;
};

#endif //__USER_H__
