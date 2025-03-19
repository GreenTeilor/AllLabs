library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity summator_2_s is
    Port ( x1 : in STD_LOGIC;
           x2 : in STD_LOGIC;
           x3 : in STD_LOGIC;
           x4 : in STD_LOGIC;
           x5 : in STD_LOGIC;
           y1 : out STD_LOGIC;
           y2 : out STD_LOGIC;
           y3 : out STD_LOGIC);
end summator_2_s;

architecture a_summator_2_s of summator_2_s is
component summator_1_s is 
    port  (
        x1, x2, x3 : in STD_LOGIC;
        y1, y2: out STD_LOGIC
    );
end component;
signal carry_from1: STD_LOGIC;
begin
    U1: summator_1_s port map (x1 => x1, x2 => x2, x3 => x5, y1 => y1, y2 => carry_from1);
    U2: summator_1_s port map (x1 => x3, x2 => x4, x3 => carry_from1, y1 => y2, y2 => y3);    
end a_summator_2_s;