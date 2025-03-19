library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity demux_4_1_s is
    Port ( s, s1, z : in STD_LOGIC;
           a, b, c, d : out STD_LOGIC
    );
end demux_4_1_s;

architecture a_demux_4_1_s of demux_4_1_s is
component and2 is
    port (
        a, b : in  STD_LOGIC;
        z : out STD_LOGIC
    );
end component;
component and3 is
        port (
            a, b, c : in  STD_LOGIC;
            z : out STD_LOGIC
        );
end component;
component or2 is
    port (
        a, b : in  STD_LOGIC;
        z  : out STD_LOGIC
    );
end component;
component inv is
        port (
            a : in  STD_LOGIC;
            z  : out STD_LOGIC
        );
end component;
signal ns, ns1: STD_LOGIC;
begin
    U1: inv port map (a => s, z => ns);
    U2: inv port map (a => s1, z => ns1);
    U3: and3 port map (a => s, b => s1, c => z, z => d);
    U4: and3 port map (a => ns, b => s1, c => z, z => c);
    U5: and3 port map (a => s, b => ns1, c => z, z => b);
    U6: and3 port map (a => ns, b => ns1, c => z, z => a);
end a_demux_4_1_s;
