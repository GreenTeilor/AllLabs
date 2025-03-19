library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity bi_stable_sim is
end bi_stable_sim;

architecture behaviour of bi_stable_sim is
component bi_stable is
    port (
        q, nq : out STD_LOGIC
    );
end component;
signal q, nq: STD_LOGIC;
begin
    US: bi_stable port map (
        q => q,
        nq => nq
    );
end behaviour;