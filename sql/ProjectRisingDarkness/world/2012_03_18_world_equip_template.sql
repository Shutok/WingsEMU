-- Equip for darkfallen blood knight
DELETE FROM creature_equip_template WHERE entry = 37595;
INSERT INTO creature_equip_template VALUES (37595, 51028, 0, 0);
UPDATE creature_template SET equipment_id = 37595 WHERE entry = 37595;

-- Equip for darkfallen tactician
DELETE FROM creature_equip_template WHERE entry = 37666;
INSERT INTO creature_equip_template VALUES (37666, 51029, 51029, 0);
UPDATE creature_template SET equipment_id = 37666 WHERE entry = 37666;

-- Equip for darkfallen commander
DELETE FROM creature_equip_template WHERE entry = 37662;
INSERT INTO creature_equip_template VALUES (37662, 51322, 0, 0);
UPDATE creature_template SET equipment_id = 37662 WHERE entry = 37662;

-- Equip for darkfallen lieutenant
DELETE FROM creature_equip_template WHERE entry = 37665;
INSERT INTO creature_equip_template VALUES (37665, 51323, 51324, 0);
UPDATE creature_template SET equipment_id = 37662 WHERE entry = 37665;