library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decoder_2_4_s is
    Port ( 
        s0, s1, c: in STD_LOGIC;
        z0, z1, z2, z3: out STD_LOGIC
    );
end decoder_2_4_s;

architecture a_decoder_2_4_s of decoder_2_4_s is
component decoder_2_1_b
    port (
        s: in STD_LOGIC;
        z0, z1: out STD_LOGIC
    );
end component;
component and2
    port (
        a, b: in STD_LOGIC;
        z: out STD_LOGIC
    );
end component;
signal y: STD_LOGIC_VECTOR(0 to 3);
signal tz: STD_LOGIC_VECTOR(0 to 3);
begin
    U1: decoder_2_1_b port map (s => s0, z0 => y(0), z1 => y(1));
    U2: decoder_2_1_b port map (s => s1, z0 => y(2), z1 => y(3));
    U3: and2 port map (a => y(0), b => y(2), z => tz(0));
    U4: and2 port map (a => y(1), b => y(2), z => tz(1));
    U5: and2 port map (a => y(0), b => y(3), z => tz(2));
    U6: and2 port map (a => y(1), b => y(3), z => tz(3));
    U7: and2 port map(a => tz(0), b => c, z => z0);
    U8: and2 port map(a => tz(1), b => c, z => z1);
    U9: and2 port map(a => tz(2), b => c, z => z2);
    U10: and2 port map(a => tz(3), b => c, z => z3);
end a_decoder_2_4_s;
