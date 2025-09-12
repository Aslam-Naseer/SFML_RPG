#pragma once

class SkillComponent
{
public:
    enum class Skills {
        Constitution = 0,
        MeleeCombat,
        RangedCombat,
        Endurance
    };

private:
    class Skill
    {
    public:
        Skills type;

        int level = 1;
        int levelCap = 99;
        int exp = 0;
        int expNext = 100;

        Skill(Skills type);
        ~Skill();

        void gainExp(const int exp);
        void loseExp(const int exp);
        void updateLevel(bool levelUp = true);
        void update();
    };

    std::vector<Skill> skills;

public:
    SkillComponent();
    ~SkillComponent();

    const int getSkill(const Skills skill) const;
    void gainExp(const Skills skill, const int exp);
};