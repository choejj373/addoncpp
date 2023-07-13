#pragma once
#include <string>
#include <list>
#include <iostream>
#include "ICombatObject.h"

class Skill;
class Party;
class CommandQ;
class Object : public ICombatObject
{
	std::list<Skill*> m_skillList;
	std::string m_name;
	int m_prevAttackTick;
	int m_hp;

	int m_damage;
	int m_attackSpeed;

	Party* m_party;

public:
    virtual ~Object();
    Object(const char* name);
    void addSkill(Skill* skill) {
        m_skillList.push_back(skill);
    }
    
    //Party* getParty() {
    //    return m_party;
    //}

    //void setParty( Party* party) {
    //    m_party = party;
    //}

    void setStat( int hp, int damage, int attackSpeed) {
//        std::cout << hp << ", " << damage << ", " << attackSpeed << std::endl;
        
        m_hp = hp;
        m_damage = damage;
        m_attackSpeed = attackSpeed;
    }

public:
    void updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam );

    //void damagedAll(int damage, std::string&);
    //void healAll(int hp, std::string&);
    bool damaged(int damage, std::string&);
    bool heal(int _hp, std::string& );

    int getHp() { return m_hp; }
    bool isDead() { return (m_hp <= 0) ? true : false; }
    std::string& getName() { return m_name; }

};

