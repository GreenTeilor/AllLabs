library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity or4 is
    Port ( a, b, c, d : in STD_LOGIC;
           z : out STD_LOGIC);
end or4;

architecture a_or4 of or4 is
component or2
    port (
        a, b : in STD_LOGIC;
        z: out STD_LOGIC
    );
end component;
signal temp1, temp2: STD_LOGIC;
begin
    U1: or2 port map (a => a, b => b, z => temp1);
    U2: or2 port map (a => c, b => d, z => temp2);
    U3: or2 port map (a => temp1, b => temp2, z => z);
end a_or4;
