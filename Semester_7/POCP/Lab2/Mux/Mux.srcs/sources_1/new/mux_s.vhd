library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity mux_s IS
port (
    a: in STD_LOGIC;
    b: in STD_LOGIC;
    s: in STD_LOGIC;
    z: out STD_LOGIC
);
end mux_s;

architecture a_mux_s of mux_s is
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
        z  : out STD_LOGIC
    );
end component;
component inv is
        port (
            a : in  STD_LOGIC;
            z  : out STD_LOGIC
        );
end component;
signal ns, nsa, sb: STD_LOGIC;
begin
    U1: inv port map (a => s, z => ns);
    U2: and2 port map (a => a, b => ns, z => nsa);
    U3: and2 port map (a => b, b => s, z => sb);
    U4: or2 port map (a => nsa, b => sb, z => z);
end;