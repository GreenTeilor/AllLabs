library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity frequency_divider is
    Port ( clk, clr : in STD_LOGIC;
           div2, div4, div8 : out STD_LOGIC);
end frequency_divider;

architecture Behavioral of frequency_divider is
component T_flip_flop_behavioral
    Port (
        t   : in STD_LOGIC;
        clk : in STD_LOGIC;
        clr : in STD_LOGIC;
        q   : out STD_LOGIC
    );
end component;
signal st1, st2, st3: std_logic;
begin
    U0: T_flip_flop_behavioral port map(t => '1', clk => clk, clr => clr, q => st1);
    U1: T_flip_flop_behavioral port map(t => '1', clk => st1, clr => clr, q => st2);
    U2: T_flip_flop_behavioral port map(t => '1', CLK => st2, clr => clr, q => st3);
    div2 <= st1;
    div4 <= st2;
    div8 <= st3;
end Behavioral;
