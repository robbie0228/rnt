enum class LinkType {Virus, Data};  // Types of a Link

class Link {
        LinkType type;  // Type of Link
        int strength;   // strength of Link
        char name;      // 'A-H' for Player 1
                        // 'a-h' for Player 2

    public:
        // Constructor for a Link
        //   The Link has given type, strength and name
        Link(LinkType type, int strength, char name);

        // Accessor/setter for type
        LinkType getType();
        void setType(LinkType newType);

        // Accessor/setter for strength
        int getStrength();
        void setStrength(int newStrength);

        // Accessor for name
        char getName();
};
