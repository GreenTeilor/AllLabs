library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity complex_mux_b is
port (
    a, b, a1, b1, s : in STD_LOGIC;
    z, z1 : out STD_LOGIC
);
end complex_mux_b;

architecture a_complex_mux_b of complex_mux_b is
begin
    z <= a when s = '0' else b;
    z1 <= a1 when s = '0' else b1;
end a_complex_mux_b;
