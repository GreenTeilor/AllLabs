library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity summator_2_b is
    Port ( x1 : in STD_LOGIC;
           x2 : in STD_LOGIC;
           x3 : in STD_LOGIC;
           x4 : in STD_LOGIC;
           x5 : in STD_LOGIC;
           y1 : out STD_LOGIC;
           y2 : out STD_LOGIC;
           y3 : out STD_LOGIC);
end summator_2_b;

architecture a_summator_2_b of summator_2_b is
signal nx1, nx2, nx3, nx4, nx5, carry_from1: STD_LOGIC;
begin
    nx1 <= not x1;
    nx2 <= not x2;
    nx3 <= not x3;
    nx4 <= not x4;
    nx5 <= not x5;
    y1 <= (nx1 and nx2 and x5) or (nx1 and x2 and nx5) or (x1 and nx2 and nx5) or (x1 and x2 and x5);
    carry_from1 <= (nx1 and x2 and x5) or (x1 and nx2 and x5) or (x1 and x2 and nx5) or (x1 and x2 and x5);
    y2 <= (nx3 and nx4 and carry_from1) or (nx3 and x4 and not carry_from1) or (x3 and nx4 and not carry_from1) or (x3 and x4 and carry_from1);
    y3 <= (nx3 and x4 and carry_from1) or (x3 and nx4 and carry_from1) or (x3 and x4 and not carry_from1) or (x3 and x4 and carry_from1);
end a_summator_2_b;
