#pragma once
#include <string>

class ICombatObject;
class Party;
class Object;
class CommandQ;
class Skill
{
    std::string m_name;
    int m_coolTimeTick;
    int m_prevProcessTick;

public:
    Skill(const char* name, int coolTimeTick);
    virtual ~Skill();
    void updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam, Object* owner);

    virtual void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object * owner) = 0;

};

class SkillDamage : public Skill {
public:
    SkillDamage(const char* name, int coolTimeTick) : Skill(name, coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillDamageWide : public Skill {
public:
    SkillDamageWide(const char* name, int coolTimeTick) : Skill(name, coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHeal : public Skill {
public:  
    SkillHeal(const char* name, int coolTimeTick) : Skill(name, coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHealWide : public Skill {
public:
    SkillHealWide(const char* name, int coolTimeTick) : Skill(name, coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};