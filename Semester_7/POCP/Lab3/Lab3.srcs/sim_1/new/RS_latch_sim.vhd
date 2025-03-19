library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity RS_latch_sim is
end RS_latch_sim;

architecture behaviour of RS_latch_sim is
component RS_latch_behavioral is
    port (
        s, r : in  STD_LOGIC;
        q, nq : out STD_LOGIC
    );
end component;
component RS_latch_structural is
    port (
        s, r : in  STD_LOGIC;
        q, nq : out STD_LOGIC
    );
end component;
component RS_latch_param is
    port (
        s, r : in  STD_LOGIC;
        q, nq : out STD_LOGIC
    );
end component;
signal s, r: STD_LOGIC;
signal q_b, nq_b: STD_LOGIC;
signal q_s, nq_s: STD_LOGIC;
signal q_p, nq_p: STD_LOGIC; 
begin
    UB: RS_latch_behavioral port map (
        s => s,
        r => r,
        q => q_b,
        nq => nq_b
    );
    US: RS_latch_structural port map (
        s => s,
        r => r,
        q => q_s,
        nq => nq_s
    );
    UP: RS_latch_param port map (
        s => s,
        r => r,
        q => q_p,
        nq => nq_p
    );
    Simulate: process
            begin
                r <= '0';
                s <= '0';
                wait for 10 ns;     
                
                r <= '1';
                s <= '0';
                wait for 10 ns;    
                
                r <= '0';
                s <= '0';
                wait for 10 ns;     
                
                r <= '0';
                s <= '1';
                wait for 10 ns;      
                
                r <= '0';
                s <= '0';
                wait for 10 ns;        
                
                r <= '1';
                s <= '1';
                wait for 10 ns;    
                
                r <= '0';
                s <= '0';
                wait for 10 ns;
    end process;
end behaviour;