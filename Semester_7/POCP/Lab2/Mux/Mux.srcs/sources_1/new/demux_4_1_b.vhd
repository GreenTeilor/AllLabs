library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity demux_4_1_b is
    Port ( s, s1, z : in STD_LOGIC;
           a, b, c, d : out STD_LOGIC
    );
end demux_4_1_b;

architecture a_demux_4_1_b of demux_4_1_b is

begin
    process (z, s, s1) is begin
        if (s ='0' and s1 = '0') then
            a <= z;
            b <= '0';
            c <= '0';
            d <= '0';
        elsif (s ='1' and s1 = '0') then
            b <= z;
            a <= '0';
            c <= '0';
            d <= '0';
        elsif (s ='0' and s1 = '1') then
            c <= z;
            a <= '0';
            b <= '0';
            d <= '0';
        else
            d <= z;
            a <= '0';
            b <= '0';
            c <= '0';
        end if;
    end process;
end a_demux_4_1_b;
