library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity D_flip_flop_enable_sim is
end D_flip_flop_enable_sim;

architecture Behavioral of D_flip_flop_enable_sim is
component D_flip_flop_enable
    Port (
        d, clk, e : in std_logic;
        q, nq   : out std_logic
    );
end component;
signal d : std_logic := '0';
signal clk : std_logic := '0';
signal e : std_logic := '1';
signal q : std_logic;
signal nq : std_logic;
begin
    U1: D_flip_flop_enable
        port map (
            d   => d,
            clk => clk,
            e => e,
            q => q,
            nq  => nq
        );
    clk <= not clk after 10ns;
    d <= not d after 40ns;
    e <= not e after 80ns;
end Behavioral;
