-- Copyright (C) 1991-2015 Altera Corporation. All rights reserved.
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, the Altera Quartus Prime License Agreement,
-- the Altera MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Altera and sold by Altera or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 15.1.0 Build 185 10/21/2015 SJ Lite Edition"

-- DATE "09/06/2025 15:52:44"

-- 
-- Device: Altera EP4CE6E22C6 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Practica2 IS
    PORT (
	s0 : OUT std_logic;
	b0 : IN std_logic;
	c0 : IN std_logic;
	a0 : IN std_logic;
	c1 : OUT std_logic
	);
END Practica2;

-- Design Ports Information
-- s0	=>  Location: PIN_30,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c1	=>  Location: PIN_32,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b0	=>  Location: PIN_28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c0	=>  Location: PIN_10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a0	=>  Location: PIN_31,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Practica2 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_s0 : std_logic;
SIGNAL ww_b0 : std_logic;
SIGNAL ww_c0 : std_logic;
SIGNAL ww_a0 : std_logic;
SIGNAL ww_c1 : std_logic;
SIGNAL \s0~output_o\ : std_logic;
SIGNAL \c1~output_o\ : std_logic;
SIGNAL \b0~input_o\ : std_logic;
SIGNAL \a0~input_o\ : std_logic;
SIGNAL \c0~input_o\ : std_logic;
SIGNAL \ss0|1~0_combout\ : std_logic;
SIGNAL \c1-3~0_combout\ : std_logic;

BEGIN

s0 <= ww_s0;
ww_b0 <= b0;
ww_c0 <= c0;
ww_a0 <= a0;
c1 <= ww_c1;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

-- Location: IOOBUF_X0_Y8_N16
\s0~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \ss0|1~0_combout\,
	devoe => ww_devoe,
	o => \s0~output_o\);

-- Location: IOOBUF_X0_Y6_N16
\c1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \c1-3~0_combout\,
	devoe => ww_devoe,
	o => \c1~output_o\);

-- Location: IOIBUF_X0_Y9_N8
\b0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b0,
	o => \b0~input_o\);

-- Location: IOIBUF_X0_Y7_N1
\a0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a0,
	o => \a0~input_o\);

-- Location: IOIBUF_X0_Y18_N15
\c0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_c0,
	o => \c0~input_o\);

-- Location: LCCOMB_X2_Y7_N0
\ss0|1~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \ss0|1~0_combout\ = \b0~input_o\ $ (\a0~input_o\ $ (\c0~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \b0~input_o\,
	datac => \a0~input_o\,
	datad => \c0~input_o\,
	combout => \ss0|1~0_combout\);

-- Location: LCCOMB_X2_Y7_N2
\c1-3~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \c1-3~0_combout\ = (\b0~input_o\ & ((\a0~input_o\) # (\c0~input_o\))) # (!\b0~input_o\ & (\a0~input_o\ & \c0~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \b0~input_o\,
	datac => \a0~input_o\,
	datad => \c0~input_o\,
	combout => \c1-3~0_combout\);

ww_s0 <= \s0~output_o\;

ww_c1 <= \c1~output_o\;
END structure;


