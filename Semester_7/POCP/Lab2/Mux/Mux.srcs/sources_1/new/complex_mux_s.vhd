library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity complex_mux_s is
port (
    a, b, a1, b1, s : in STD_LOGIC;
    z, z1 : out STD_LOGIC
);
end complex_mux_s;

architecture a_complex_mux_s of complex_mux_s is
component mux_s is
    port (
        a, b, s : in  STD_LOGIC;
        z  : out STD_LOGIC
    );
end component;
begin
    U1: mux_s port map (a => a, b => b, s => s, z => z);
    U2: mux_s port map (a => a1, b => b1, s => s, z => z1);
end a_complex_mux_s;
