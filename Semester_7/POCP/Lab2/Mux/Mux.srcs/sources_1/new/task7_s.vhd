library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task7_s is
    Port ( w : in STD_LOGIC;
           x : in STD_LOGIC;
           y : in STD_LOGIC;
           z : in STD_LOGIC;
           g : out STD_LOGIC);
end task7_s;

architecture a_task7_s of task7_s is
component and3 is
    port (
        a : in  STD_LOGIC;
        b : in  STD_LOGIC;
        c : in  STD_LOGIC;
        z : out STD_LOGIC
    );
end component;
component and2 is
    port (
        a : in  STD_LOGIC;
        b : in  STD_LOGIC;
        z : out STD_LOGIC
    );
end component;
component or2 is
    port (
        a : in  STD_LOGIC;
        b : in  STD_LOGIC;
        z : out STD_LOGIC
    );
end component;
signal and3z, and2z: STD_LOGIC;
begin
    U1: and3 port map (a => w, b => x, c => y, z => and3z);
    U2: and2 port map (a => y, b => z, z => and2z);
    U3: or2 port map (a => and3z, b => and2z, z => g);
end a_task7_s;
