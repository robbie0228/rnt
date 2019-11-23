// Type of link
enum class LinkType {Virus, Data};

class Link {
    LinkType type; // Type of link
    int strength; // Strength of link
    

    public:
        Link(LinkType type, int strength); // Creates the link with given type and strength
        bool battle(Link *other); // Battles another link and returns 1 if survived, and 0 otherwise

        // Getters/Accessors for fields
        LinkType getType();
        void setType(LinkType newType);
        LinkType getStrength();
        void setStrength(int newStrength);
        
};
