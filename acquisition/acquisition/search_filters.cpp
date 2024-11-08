#include <acquisition/search_filters.h>

#include <acquisition/float_filter.h>
#include <acquisition/proxy_model.h>

const QStringList SearchFilters::s_item_categories = {
    "Any",
    "Any Weapon",
    "One-Handed Weapon",
    "One-Handed Melee Weapon",
    "Two-Handed Melee Weapon",
    "Bow",
    "Claw",
    "Any Dagger",
    "Base Dagger",
    "Rune Dagger",
    "One-Handed Axe",
    "One-Handed Sword",
    "Any One-handed Mace",
    "Base One-Handed Mace",
    "Sceptre",
    "Any Staff",
    "Base Staff",
    "Warstaff",
    "Two-Handed Axe",
    "Two-Handed Mace",
    "Two-Handed Sword",
    "Wand",
    "Fishing Rod",
    "Any Armour",
    "Body Armour",
    "Boots",
    "Gloves",
    "Helmet",
    "Shield",
    "Quiver",
    "Any Acessory",
    "Amulet",
    "Belt",
    "Ring",
    "Trinket",
    "Any Gem",
    "Skill Gem",
    "Support Gem",
    "Awakened Support Gem",
    "Any Jewel",
    "Base Jewel",
    "Abyss Jewel",
    "Cluster Jewel",
    "Flask",
    "Map",
    "Map Fragment",
    "Breachstone",
    "Maven's Invitation",
    "Scarab",
    "Leaguestone",
    "Memory Line",
    "Divination Card",
    "Captured Beast",
    "Any Heist Equipment",
    "Heist Gear",
    "Heist Tool",
    "Heist Cloak",
    "Heist Brooch",
    "Any Heist Mission",
    "Heist Contract",
    "Heist Blueprint",
    "Any Expedition Logbook",
    "Sanctum Research",
    "Sanctum Relic",
    "Any Tincture",
    "Any Corpse",
    "Any Currency",
    "Unique Fragment",
    "Resonator",
    "Fossil",
    "Incubator",
    "Heist Target",
    "Omen",
    "Tatoo"
};

const QStringList SearchFilters::s_item_rarities = {
    "Any",
    "Normal",
    "Magic",
    "Rare",
    "Unique",
    "Unique (Foil)",
    "Any Non-Unique"
};

const QStringList SearchFilters::s_character_classes = {
    "Any",
    "Scion",
    "Marauder",
    "Ranger",
    "Witch",
    "Duelist",
    "Templar",
    "Shadow"
};

const QStringList SearchFilters::s_map_series = {
    "Any",
    "Current",
    "Settlers",
    "Necropolis",
    "Affliction",
    "Ancestor",
    "Crucible",
    "Sanctum",
    "Kalandra",
    "Sentinel",
    "Archnemesis",
    "Scourge",
    "Expedition",
    "Ritual",
    "Heist",
    "Harvest",
    "Delirium",
    "Metamorph",
    "Blight",
    "Legion",
    "Synthesis",
    "Betrayal",
    "War for the Atlas",
    "Atlas of Worlds",
    "The Awakening",
    "Legacy"
};

const QStringList SearchFilters::s_map_completion_rewards = {
    "Any",
    "Abberath's Horn",
    "Actum",
    "Advancing Fortress",
    "Agnerod",
    "Agnerod East",
    "Agnerod North",
    "Agnerod South",
    "Agnerod West",
    "Ahn's Might",
    "Al Dhih",
    "Allure",
    "Amplification Rod",
    "Apep's Rage",
    "Apep's Rage",
    "Arakaali's Fang",
    "Arborix",
    "Ashcaller",
    "Ashcaller",
    "Ashes of the Sun",
    "Atziri's Disfavour",
    "Atziri's Rule",
    "Augyre",
    "Aurumvorax",
    "Axiom Perpetuum",
    "Balefire",
    "Beltimber Blade",
    "Bino's Kitchen Knife",
    "Bitterdream",
    "Blood of Summer",
    "Bloodplay",
    "Bloodseeker",
    "Brain Rattler",
    "Breath of the Council",
    "Brightbeak",
    "Brutus' Lead Sprinkler",
    "Callinellus Malleus",
    "Cameria's Avarice",
    "Cameria's Maul",
    "Cane of Kulemak",
    "Cane of Unravelling",
    "Cerberus Limb",
    "Chaber Cairn",
    "Chin Sol",
    "Chitus' Needle",
    "Chober Chaber",
    "Clayshaper",
    "Cold Iron Point",
    "Corona Solaris",
    "Cospri's Malice",
    "Cybil's Paw",
    "Daresso's Passion",
    "Darkscorn",
    "Death's Hand",
    "Death's Harp",
    "Death's Opus",
    "Debeon's Dirge",
    "Demigod's Authority",
    "Disintegrator",
    "Divinarius",
    "Doomfletch",
    "Doomfletch's Prism",
    "Doomsower",
    "Doon Cuebiyari",
    "Doryani's Catalyst",
    "Dreadarc",
    "Dreadbeak",
    "Dreadsurge",
    "Dreamfeather",
    "Duskdawn",
    "Dyadus",
    "Dying Breath",
    "Dying Breath",
    "Earendel's Embrace",
    "Echoforge",
    "Eclipse Solaris",
    "Eclipse Solaris",
    "Edge of Madness",
    "Ephemeral Edge",
    "Essentia Sanguis",
    "Essentia Sanguis",
    "Ewar's Mirage",
    "Fate of the Vaal",
    "Femurs of the Saints",
    "Fencoil",
    "Fidelitas' Spike",
    "Flesh-Eater",
    "Fragment of Eternity",
    "Frostbreath",
    "Geofri's Baptism",
    "Geofri's Devotion",
    "Goblinedge",
    "Gorebreaker",
    "Goredrill",
    "Grace of the Goddess",
    "Grelwood Shank",
    "Hand of Thought and Motion",
    "Hand of Thought and Motion",
    "Hand of Wisdom and Action",
    "Heartbreaker",
    "Hegemony's Era",
    "Hezmana's Bloodlust",
    "Hiltless",
    "Hopeshredder",
    "Hrimnor's Dirge",
    "Hrimnor's Hymn",
    "Hyaon's Fury",
    "Ichimonji",
    "Infractem",
    "Innsbury Edge",
    "Iron Commander",
    "Izaro's Dilemma",
    "Jack, the Axe",
    "Jorrhast's Blacksteel",
    "Kaom's Primacy",
    "Kingmaker",
    "Kitava's Feast",
    "Kondo's Pride",
    "Kongor's Undying Rage",
    "Lakishu's Blade",
    "Last Resort",
    "Lavianga's Wisdom",
    "Law of the Wilds",
    "Lifesprig",
    "Limbsplit",
    "Lioneye's Glare",
    "Maata's Teaching",
    "Mark of the Doubting Knight",
    "Marohi Erqi",
    "Martyr of Innocence",
    "Midnight Bargain",
    "Mightflay",
    "Mirebough",
    "Mjölner",
    "Mon'tregul's Grasp",
    "Moonbender's Wing",
    "Moonsorrow",
    "Mortem Morsu",
    "Nametaker",
    "Nebulis",
    "Nebuloch",
    "Ngamahu's Flame",
    "Null's Inclination",
    "Nuro's Harp",
    "Nycta's Lantern",
    "Obliteration",
    "Obliteration",
    "Oni-Goroshi",
    "Ornament of the East",
    "Oro's Sacrifice",
    "Panquetzaliztli",
    "Paradoxica",
    "Pillar of the Caged God",
    "Pillar of the Caged God",
    "Piscator's Vigil",
    "Piscator's Vigil",
    "Pledge of Hands",
    "Prismatic Eclipse",
    "Quecholli",
    "Queen's Decree",
    "Queen's Escape",
    "Quill Rain",
    "Rakiata's Dance",
    "Razor of the Seventh Sun",
    "Reach of the Council",
    "Realm Ender",
    "Realmshaper",
    "Reaper's Pursuit",
    "Rebuke of the Vaal",
    "Redbeak",
    "Reefbane",
    "Relentless Fury",
    "Relic of the Cycle",
    "Relic of the Pact",
    "Relic of the Pact",
    "Replica Advancing Fortress",
    "Replica Allure",
    "Replica Bitterdream",
    "Replica Bloodplay",
    "Replica Blood Thorn",
    "Replica Cold Iron Point",
    "Replica Dreamfeather",
    "Replica Duskdawn",
    "Replica Earendel's Embrace",
    "Replica Fencoil",
    "Replica Frostbreath",
    "Replica Harvest",
    "Replica Heartbreaker",
    "Replica Infractem",
    "Replica Innsbury Edge",
    "Replica Iron Commander",
    "Replica Kongor's Undying Rage",
    "Replica Last Resort",
    "Replica Midnight Bargain",
    "Replica Nebulis",
    "Replica Oro's Sacrifice",
    "Replica Paradoxica",
    "Replica Quill Rain",
    "Replica Soul Taker",
    "Replica Tempestuous Steel",
    "Replica Trypanon",
    "Replica Tulfall",
    "Replica Tulfall",
    "Replica Twyzel",
    "Replica Ungil's Gauche",
    "Replica Windripper",
    "Replica Wings of Entropy",
    "Reverberation Rod",
    "Rigwald's Charge",
    "Rigwald's Command",
    "Rigwald's Savagery",
    "Rive",
    "Roth's Reach",
    "Rust of Winter",
    "Sanguine Gambol",
    "Scaeva",
    "Scar of Fate",
    "Serle's Masterwork",
    "Severed in Sleep",
    "Shade of Solaris",
    "Shimmeron",
    "Shiversting",
    "Sign of the Sin Eater",
    "Silverbough",
    "Silverbranch",
    "Singularity",
    "Sinvicta's Mettle",
    "Sire of Shards",
    "Slivertongue",
    "Song of the Sirens",
    "Soul Taker",
    "Soulwrest",
    "Spine of the First Claimant",
    "Splinter of the Moon",
    "Starforge",
    "Storm Cloud",
    "Storm Prison",
    "Storm Prison",
    "Story of the Vaal",
    "Story of the Vaal",
    "Taproot",
    "Taryn's Shiver",
    "Tawhoa's Felling",
    "Terminus Est",
    "The Annihilating Light",
    "The Black Cane",
    "The Blood Reaper",
    "The Blood Thorn",
    "The Burden of Shadows",
    "The Cauteriser",
    "The Consuming Dark",
    "The Crimson Storm",
    "The Dancing Dervish",
    "The Dancing Duo",
    "The Dark Seer",
    "The Enmity Divine",
    "The Fulcrum",
    "The Geomantic Gyre",
    "The Gluttonous Tide",
    "The Goddess Bound",
    "The Goddess Scorned",
    "The Goddess Unleashed",
    "The Grey Spire",
    "The Gryphon",
    "The Harvest",
    "The Hidden Blade",
    "The Iron Mass",
    "The Living Blade",
    "The Poet's Pen",
    "The Princess",
    "The Redblade",
    "The Rippling Thoughts",
    "The Saviour",
    "The Scourge",
    "The Screaming Eagle",
    "The Searing Touch",
    "The Searing Touch",
    "The Stormheart",
    "The Stormwall",
    "The Supreme Truth",
    "The Surging Thoughts",
    "The Tempest",
    "The Tempestuous Steel",
    "The Wasp Nest",
    "The Whispering Ice",
    "The Winds of Fate",
    "The Yielding Mortality",
    "Thunder of the Dawn",
    "Tidebreaker",
    "Tipua Kaikohuru",
    "Touch of Anguish",
    "Tremor Rod",
    "Trypanon",
    "Tulborn",
    "Tulborn",
    "Tulfall",
    "Tulfall",
    "Twyzel",
    "Ungil's Gauche",
    "United in Dream",
    "Uul-Netol's Embrace",
    "Uul-Netol's Kiss",
    "Uul-Netol's Kiss",
    "Varunastra",
    "Vestige of Divinity",
    "Void Battery",
    "Voidforge",
    "Voidhome",
    "Voltaxic Rift",
    "Vulconus",
    "White Wind",
    "Wideswing",
    "Widowhail",
    "Widowmaker",
    "Wildslash",
    "Windripper",
    "Wings of Entropy",
    "Wings of Entropy",
    "Witchhunter's Judgment",
    "Xirgil's Crank",
    "Xoph's Inception",
    "Xoph's Inception",
    "Xoph's Nurture",
    "Yaomac's Accord",
    "Abberath's Hooves",
    "Abhorrent Interrogation",
    "Abyssus",
    "Admiral's Arrogance",
    "Aegis Aurora",
    "Ahn's Contempt",
    "Ahn's Heritage",
    "Ahuana's Bite",
    "Akoya's Gaze",
    "Alberon's Warpath",
    "Algor Mortis",
    "Allelopathy",
    "Allelopathy",
    "Alpha's Howl",
    "Ambu's Charge",
    "Ancient Skull",
    "Annihilation's Approach",
    "Apep's Slumber",
    "Apep's Slumber",
    "Apep's Supremacy",
    "Architect's Hand",
    "Architect's Hand",
    "Asenath's Chant",
    "Asenath's Gentle Touch",
    "Asenath's Mark",
    "Ashrend",
    "Asphyxia's Wrath",
    "Asphyxia's Wrath",
    "Assailum",
    "Atziri's Acuity",
    "Atziri's Mirror",
    "Atziri's Reflection",
    "Atziri's Splendour",
    "Atziri's Step",
    "Aukuna's Will",
    "Aurseize",
    "Beacon of Madness",
    "Belly of the Beast",
    "Bitterbind Point",
    "Blackgleam",
    "Blackgleam",
    "Blackgleam",
    "Black Sun Crest",
    "Black Zenith",
    "Blasphemer's Grasp",
    "Bloodbond",
    "Blood Price",
    "Blunderbore",
    "Bones of Ullr",
    "Bramblejack",
    "Breathstealer",
    "Brinerot Flag",
    "Brinerot Whalers",
    "Briskwrap",
    "Briskwrap",
    "Broadstroke",
    "Broken Faith",
    "Bronn's Lithe",
    "Bubonic Trail",
    "Cadigan's Crown",
    "Carcass Jack",
    "Ceaseless Feast",
    "Chains of Command",
    "Chalice of Horrors",
    "Chernobog's Pillar",
    "Cherrubim's Maleficence",
    "Chitus' Apex",
    "Cloak of Defiance",
    "Cloak of Flame",
    "Cloak of Tawm'r Isley",
    "Command of the Pit",
    "Corpsewalker",
    "Cospri's Will",
    "Cowl of the Ceraunophile",
    "Cowl of the Cryophile",
    "Cowl of the Thermophile",
    "Cragfall",
    "Craghead",
    "Craiceann's Carapace",
    "Craiceann's Chitin",
    "Craiceann's Pincers",
    "Craiceann's Tracks",
    "Crest of Desire",
    "Crest of Perandus",
    "Crown of Eyes",
    "Crown of the Inward Eye",
    "Crown of the Pale King",
    "Crown of the Tyrant",
    "Crown of Thorns",
    "Crystal Vault",
    "Curtain Call",
    "Dance of the Offered",
    "Dance of the Offered",
    "Daresso's Courage",
    "Daresso's Defiance",
    "Darkray Vectors",
    "Dawnbreaker",
    "Dawnstrider",
    "Death's Door",
    "Death's Oath",
    "Deerstalker",
    "Deidbell",
    "Deidbellow",
    "Demigod's Beacon",
    "Demigod's Dominance",
    "Demigod's Immortality",
    "Demigod's Stride",
    "Demigod's Touch",
    "Demigod's Triumph",
    "Demon Stitcher",
    "Dendrobate",
    "Deshret's Vise",
    "Devoto's Devotion",
    "Dialla's Malefaction",
    "Doedre's Malevolence",
    "Doedre's Scorn",
    "Doedre's Skin",
    "Doedre's Tenure",
    "Doppelgänger Guise",
    "Doryani's Delusion",
    "Doryani's Delusion",
    "Doryani's Delusion",
    "Doryani's Fist",
    "Doryani's Prototype",
    "Drillneck",
    "Duskblight",
    "Duskblight",
    "Dusktoe",
    "Dusktoe",
    "Eber's Unification",
    "Echoes of Creation",
    "El'Abin's Visage",
    "Elevore",
    "Emperor's Vigilance",
    "Empire's Grasp",
    "Entropic Devastation",
    "Esh's Mirror",
    "Esh's Mirror",
    "Esh's Visage",
    "Expedition's End",
    "Eye of Malice",
    "Ezomyte Hold",
    "Ezomyte Peak",
    "Facebreaker",
    "Fairgraves' Tricorne",
    "Faithguard",
    "Farrul's Bite",
    "Farrul's Chase",
    "Farrul's Fur",
    "Farrul's Pounce",
    "Fenumus' Shroud",
    "Fenumus' Spinnerets",
    "Fenumus' Toxins",
    "Fenumus' Weave",
    "Flamesight",
    "Flesh and Spirit",
    "Fleshcrafter",
    "Font of Thunder",
    "Forbidden Shako",
    "Fox's Fortune",
    "Foxshade",
    "Fractal Thoughts",
    "Frostferno",
    "Galesight",
    "Gamblesprint",
    "Gang's Momentum",
    "Garb of the Ephemeral",
    "Garukhan's Flight",
    "Geofri's Crest",
    "Geofri's Legacy",
    "Geofri's Sanctuary",
    "Ghostwrithe",
    "Giantsbane",
    "Glimpse of Chaos",
    "Glitterdisc",
    "Goldrim",
};

const QStringList SearchFilters::s_heist_contract_objective_values = {
    "Any",
    "Moderate Value",
    "High Value",
    "Precious",
    "Priceless"
};

const QStringList SearchFilters::s_ultimatum_challenge_types = {
    "Any",
    "Defeat Waves of Enemies",
    "Survive",
    "Protect the Altar",
    "Stand in the Stone Circles"
};

const QStringList SearchFilters::s_ultimatum_reward_types = {
    "Any",
    "Currency",
    "Divination Cards",
    "Mirrored Rare Item",
    "Unique Item"
};

const QStringList SearchFilters::s_ultimatum_required_items = {
    "Any",
    "Abberath's Horn",
    "Actum",
    "Advancing Fortress",
    "Agnerod",
    "Agnerod East",
    "Agnerod North",
    "Agnerod South",
    "Agnerod West",
    "Ahn's Might",
    "Al Dhih",
    "Allure",
    "Amplification Rod",
    "Apep's Rage",
    "Apep's Rage",
    "Arakaali's Fang",
    "Arborix",
    "Ashcaller",
    "Ashcaller",
    "Ashes of the Sun",
    "Atziri's Disfavour",
    "Atziri's Rule",
    "Augyre",
    "Aurumvorax",
    "Axiom Perpetuum",
    "Balefire",
    "Beltimber Blade",
    "Bino's Kitchen Knife",
    "Bitterdream",
    "Blood of Summer",
    "Bloodplay",
    "Bloodseeker",
    "Brain Rattler",
    "Breath of the Council",
    "Brightbeak",
    "Brutus' Lead Sprinkler",
    "Callinellus Malleus",
    "Cameria's Avarice",
    "Cameria's Maul",
    "Cane of Kulemak",
    "Cane of Unravelling",
    "Cerberus Limb",
    "Chaber Cairn",
    "Chin Sol",
    "Chitus' Needle",
    "Chober Chaber",
    "Clayshaper",
    "Cold Iron Point",
    "Corona Solaris",
    "Cospri's Malice",
    "Cybil's Paw",
    "Daresso's Passion",
    "Darkscorn",
    "Death's Hand",
    "Death's Harp",
    "Death's Opus",
    "Debeon's Dirge",
    "Demigod's Authority",
    "Disintegrator",
    "Divinarius",
    "Doomfletch",
    "Doomfletch's Prism",
    "Doomsower",
    "Doon Cuebiyari",
    "Doryani's Catalyst",
    "Dreadarc",
    "Dreadbeak",
    "Dreadsurge",
    "Dreamfeather",
    "Duskdawn",
    "Dyadus",
    "Dying Breath",
    "Dying Breath",
    "Earendel's Embrace",
    "Echoforge",
    "Eclipse Solaris",
    "Eclipse Solaris",
    "Edge of Madness",
    "Ephemeral Edge",
    "Essentia Sanguis",
    "Essentia Sanguis",
    "Ewar's Mirage",
    "Fate of the Vaal",
    "Femurs of the Saints",
    "Fencoil",
    "Fidelitas' Spike",
    "Flesh-Eater",
    "Fragment of Eternity",
    "Frostbreath",
    "Geofri's Baptism",
    "Geofri's Devotion",
    "Goblinedge",
    "Gorebreaker",
    "Goredrill",
    "Grace of the Goddess",
    "Grelwood Shank",
    "Hand of Thought and Motion",
    "Hand of Thought and Motion",
    "Hand of Wisdom and Action",
    "Heartbreaker",
    "Hegemony's Era",
    "Hezmana's Bloodlust",
    "Hiltless",
    "Hopeshredder",
    "Hrimnor's Dirge",
    "Hrimnor's Hymn",
    "Hyaon's Fury",
    "Ichimonji",
    "Infractem",
    "Innsbury Edge",
    "Iron Commander",
    "Izaro's Dilemma",
    "Jack, the Axe",
    "Jorrhast's Blacksteel",
    "Kaom's Primacy",
    "Kingmaker",
    "Kitava's Feast",
    "Kondo's Pride",
    "Kongor's Undying Rage",
    "Lakishu's Blade",
    "Last Resort",
    "Lavianga's Wisdom",
    "Law of the Wilds",
    "Lifesprig",
    "Limbsplit",
    "Lioneye's Glare",
    "Maata's Teaching",
    "Mark of the Doubting Knight",
    "Marohi Erqi",
    "Martyr of Innocence",
    "Midnight Bargain",
    "Mightflay",
    "Mirebough",
    "Mjölner",
    "Mon'tregul's Grasp",
    "Moonbender's Wing",
    "Moonsorrow",
    "Mortem Morsu",
    "Nametaker",
    "Nebulis",
    "Nebuloch",
    "Ngamahu's Flame",
    "Null's Inclination",
    "Nuro's Harp",
    "Nycta's Lantern",
    "Obliteration",
    "Obliteration",
    "Oni-Goroshi",
    "Ornament of the East",
    "Oro's Sacrifice",
    "Panquetzaliztli",
    "Paradoxica",
    "Pillar of the Caged God",
    "Pillar of the Caged God",
    "Piscator's Vigil",
    "Piscator's Vigil",
    "Pledge of Hands",
    "Prismatic Eclipse",
    "Quecholli",
    "Queen's Decree",
    "Queen's Escape",
    "Quill Rain",
    "Rakiata's Dance",
    "Razor of the Seventh Sun",
    "Reach of the Council",
    "Realm Ender",
    "Realmshaper",
    "Reaper's Pursuit",
    "Rebuke of the Vaal",
    "Redbeak",
    "Reefbane",
    "Relentless Fury",
    "Relic of the Cycle",
    "Relic of the Pact",
    "Relic of the Pact",
    "Replica Advancing Fortress",
    "Replica Allure",
    "Replica Bitterdream",
    "Replica Bloodplay",
    "Replica Blood Thorn",
    "Replica Cold Iron Point",
    "Replica Dreamfeather",
    "Replica Duskdawn",
    "Replica Earendel's Embrace",
    "Replica Fencoil",
    "Replica Frostbreath",
    "Replica Harvest",
    "Replica Heartbreaker",
    "Replica Infractem",
    "Replica Innsbury Edge",
    "Replica Iron Commander",
    "Replica Kongor's Undying Rage",
    "Replica Last Resort",
    "Replica Midnight Bargain",
    "Replica Nebulis",
    "Replica Oro's Sacrifice",
    "Replica Paradoxica",
    "Replica Quill Rain",
    "Replica Soul Taker",
    "Replica Tempestuous Steel",
    "Replica Trypanon",
    "Replica Tulfall",
    "Replica Tulfall",
    "Replica Twyzel",
    "Replica Ungil's Gauche",
    "Replica Windripper",
    "Replica Wings of Entropy",
    "Reverberation Rod",
    "Rigwald's Charge",
    "Rigwald's Command",
    "Rigwald's Savagery",
    "Rive",
    "Roth's Reach",
    "Rust of Winter",
    "Sanguine Gambol",
    "Scaeva",
    "Scar of Fate",
    "Serle's Masterwork",
    "Severed in Sleep",
    "Shade of Solaris",
    "Shimmeron",
    "Shiversting",
    "Sign of the Sin Eater",
    "Silverbough",
    "Silverbranch",
    "Singularity",
    "Sinvicta's Mettle",
    "Sire of Shards",
    "Slivertongue",
    "Song of the Sirens",
    "Soul Taker",
    "Soulwrest",
    "Spine of the First Claimant",
    "Splinter of the Moon",
    "Starforge",
    "Storm Cloud",
    "Storm Prison",
    "Storm Prison",
    "Story of the Vaal",
    "Story of the Vaal",
    "Taproot",
    "Taryn's Shiver",
    "Tawhoa's Felling",
    "Terminus Est",
    "The Annihilating Light",
    "The Black Cane",
    "The Blood Reaper",
    "The Blood Thorn",
    "The Burden of Shadows",
    "The Cauteriser",
    "The Consuming Dark",
    "The Crimson Storm",
    "The Dancing Dervish",
    "The Dancing Duo",
    "The Dark Seer",
    "The Enmity Divine",
    "The Fulcrum",
    "The Geomantic Gyre",
    "The Gluttonous Tide",
    "The Goddess Bound",
    "The Goddess Scorned",
    "The Goddess Unleashed",
    "The Grey Spire",
    "The Gryphon",
    "The Harvest",
    "The Hidden Blade",
    "The Iron Mass",
    "The Living Blade",
    "The Poet's Pen",
    "The Princess",
    "The Redblade",
    "The Rippling Thoughts",
    "The Saviour",
    "The Scourge",
    "The Screaming Eagle",
    "The Searing Touch",
    "The Searing Touch",
    "The Stormheart",
    "The Stormwall",
    "The Supreme Truth",
    "The Surging Thoughts",
    "The Tempest",
    "The Tempestuous Steel",
    "The Wasp Nest",
    "The Whispering Ice",
    "The Winds of Fate",
    "The Yielding Mortality",
    "Thunder of the Dawn",
    "Tidebreaker",
    "Tipua Kaikohuru",
    "Touch of Anguish",
    "Tremor Rod",
    "Trypanon",
    "Tulborn",
    "Tulborn",
    "Tulfall",
    "Tulfall",
    "Twyzel",
    "Ungil's Gauche",
    "United in Dream",
    "Uul-Netol's Embrace",
    "Uul-Netol's Kiss",
    "Uul-Netol's Kiss",
    "Varunastra",
    "Vestige of Divinity",
    "Void Battery",
    "Voidforge",
    "Voidhome",
    "Voltaxic Rift",
    "Vulconus",
    "White Wind",
    "Wideswing",
    "Widowhail",
    "Widowmaker",
    "Wildslash",
    "Windripper",
    "Wings of Entropy",
    "Wings of Entropy",
    "Witchhunter's Judgment",
    "Xirgil's Crank",
    "Xoph's Inception",
    "Xoph's Inception",
    "Xoph's Nurture",
    "Yaomac's Accord",
    "Abberath's Hooves",
    "Abhorrent Interrogation",
    "Abyssus",
    "Admiral's Arrogance",
    "Aegis Aurora",
    "Ahn's Contempt",
    "Ahn's Heritage",
    "Ahuana's Bite",
    "Akoya's Gaze",
    "Alberon's Warpath",
    "Algor Mortis",
    "Allelopathy",
    "Allelopathy",
    "Alpha's Howl",
    "Ambu's Charge",
    "Ancient Skull",
    "Annihilation's Approach",
    "Apep's Slumber",
    "Apep's Slumber",
    "Apep's Supremacy",
    "Architect's Hand",
    "Architect's Hand",
    "Asenath's Chant",
    "Asenath's Gentle Touch",
    "Asenath's Mark",
    "Ashrend",
    "Asphyxia's Wrath",
    "Asphyxia's Wrath",
    "Assailum",
    "Atziri's Acuity",
    "Atziri's Mirror",
    "Atziri's Reflection",
    "Atziri's Splendour",
    "Atziri's Step",
    "Aukuna's Will",
    "Aurseize",
    "Beacon of Madness",
    "Belly of the Beast",
    "Bitterbind Point",
    "Blackgleam",
    "Blackgleam",
    "Blackgleam",
    "Black Sun Crest",
    "Black Zenith",
    "Blasphemer's Grasp",
    "Bloodbond",
    "Blood Price",
    "Blunderbore",
    "Bones of Ullr",
    "Bramblejack",
    "Breathstealer",
    "Brinerot Flag",
    "Brinerot Whalers",
    "Briskwrap",
    "Briskwrap",
    "Broadstroke",
    "Broken Faith",
    "Bronn's Lithe",
    "Bubonic Trail",
    "Cadigan's Crown",
    "Carcass Jack",
    "Ceaseless Feast",
    "Chains of Command",
    "Chalice of Horrors",
    "Chernobog's Pillar",
    "Cherrubim's Maleficence",
    "Chitus' Apex",
    "Cloak of Defiance",
    "Cloak of Flame",
    "Cloak of Tawm'r Isley",
    "Command of the Pit",
    "Corpsewalker",
    "Cospri's Will",
    "Cowl of the Ceraunophile",
    "Cowl of the Cryophile",
    "Cowl of the Thermophile",
    "Cragfall",
    "Craghead",
    "Craiceann's Carapace",
    "Craiceann's Chitin",
    "Craiceann's Pincers",
    "Craiceann's Tracks",
    "Crest of Desire",
    "Crest of Perandus",
    "Crown of Eyes",
    "Crown of the Inward Eye",
    "Crown of the Pale King",
    "Crown of the Tyrant",
    "Crown of Thorns",
    "Crystal Vault",
    "Curtain Call",
    "Dance of the Offered",
    "Dance of the Offered",
    "Daresso's Courage",
    "Daresso's Defiance",
    "Darkray Vectors",
    "Dawnbreaker",
    "Dawnstrider",
    "Death's Door",
    "Death's Oath",
    "Deerstalker",
    "Deidbell",
    "Deidbellow",
    "Demigod's Beacon",
    "Demigod's Dominance",
    "Demigod's Immortality",
    "Demigod's Stride",
    "Demigod's Touch",
    "Demigod's Triumph",
    "Demon Stitcher",
    "Dendrobate",
    "Deshret's Vise",
    "Devoto's Devotion",
    "Dialla's Malefaction",
    "Doedre's Malevolence",
    "Doedre's Scorn",
    "Doedre's Skin",
    "Doedre's Tenure",
    "Doppelgänger Guise",
    "Doryani's Delusion",
    "Doryani's Delusion",
    "Doryani's Delusion",
    "Doryani's Fist",
    "Doryani's Prototype",
    "Drillneck",
    "Duskblight",
    "Duskblight",
    "Dusktoe",
    "Dusktoe",
    "Eber's Unification",
    "Echoes of Creation",
    "El'Abin's Visage",
    "Elevore",
    "Emperor's Vigilance",
    "Empire's Grasp",
    "Entropic Devastation",
    "Esh's Mirror",
    "Esh's Mirror",
    "Esh's Visage",
    "Expedition's End",
    "Eye of Malice",
    "Ezomyte Hold",
    "Ezomyte Peak",
    "Facebreaker",
    "Fairgraves' Tricorne",
    "Faithguard",
    "Farrul's Bite",
    "Farrul's Chase",
    "Farrul's Fur",
    "Farrul's Pounce",
    "Fenumus' Shroud",
    "Fenumus' Spinnerets",
    "Fenumus' Toxins",
    "Fenumus' Weave",
    "Flamesight",
    "Flesh and Spirit",
    "Fleshcrafter",
    "Font of Thunder",
    "Forbidden Shako",
    "Fox's Fortune",
    "Foxshade",
    "Fractal Thoughts",
    "Frostferno",
    "Galesight",
    "Gamblesprint",
    "Gang's Momentum",
    "Garb of the Ephemeral",
    "Garukhan's Flight",
    "Geofri's Crest",
    "Geofri's Legacy",
    "Geofri's Sanctuary",
    "Ghostwrithe",
    "Giantsbane",
    "Glimpse of Chaos",
    "Glitterdisc",
    "Goldrim",
};

const QStringList SearchFilters::s_ultimatum_reward_uniques = {
    "Any",
    "Abberath's Horn",
    "Actum",
    "Advancing Fortress",
    "Agnerod",
    "Agnerod East",
    "Agnerod North",
    "Agnerod South",
    "Agnerod West",
    "Ahn's Might",
    "Al Dhih",
    "Allure",
    "Amplification Rod",
    "Apep's Rage",
    "Apep's Rage",
    "Arakaali's Fang",
    "Arborix",
    "Ashcaller",
    "Ashcaller",
    "Ashes of the Sun",
    "Atziri's Disfavour",
    "Atziri's Rule",
    "Augyre",
    "Aurumvorax",
    "Axiom Perpetuum",
    "Balefire",
    "Beltimber Blade",
    "Bino's Kitchen Knife",
    "Bitterdream",
    "Blood of Summer",
    "Bloodplay",
    "Bloodseeker",
    "Brain Rattler",
    "Breath of the Council",
    "Brightbeak",
    "Brutus' Lead Sprinkler",
    "Callinellus Malleus",
    "Cameria's Avarice",
    "Cameria's Maul",
    "Cane of Kulemak",
    "Cane of Unravelling",
    "Cerberus Limb",
    "Chaber Cairn",
    "Chin Sol",
    "Chitus' Needle",
    "Chober Chaber",
    "Clayshaper",
    "Cold Iron Point",
    "Corona Solaris",
    "Cospri's Malice",
    "Cybil's Paw",
    "Daresso's Passion",
    "Darkscorn",
    "Death's Hand",
    "Death's Harp",
    "Death's Opus",
    "Debeon's Dirge",
    "Demigod's Authority",
    "Disintegrator",
    "Divinarius",
    "Doomfletch",
    "Doomfletch's Prism",
    "Doomsower",
    "Doon Cuebiyari",
    "Doryani's Catalyst",
    "Dreadarc",
    "Dreadbeak",
    "Dreadsurge",
    "Dreamfeather",
    "Duskdawn",
    "Dyadus",
    "Dying Breath",
    "Dying Breath",
    "Earendel's Embrace",
    "Echoforge",
    "Eclipse Solaris",
    "Eclipse Solaris",
    "Edge of Madness",
    "Ephemeral Edge",
    "Essentia Sanguis",
    "Essentia Sanguis",
    "Ewar's Mirage",
    "Fate of the Vaal",
    "Femurs of the Saints",
    "Fencoil",
    "Fidelitas' Spike",
    "Flesh-Eater",
    "Fragment of Eternity",
    "Frostbreath",
    "Geofri's Baptism",
    "Geofri's Devotion",
    "Goblinedge",
    "Gorebreaker",
    "Goredrill",
    "Grace of the Goddess",
    "Grelwood Shank",
    "Hand of Thought and Motion",
    "Hand of Thought and Motion",
    "Hand of Wisdom and Action",
    "Heartbreaker",
    "Hegemony's Era",
    "Hezmana's Bloodlust",
    "Hiltless",
    "Hopeshredder",
    "Hrimnor's Dirge",
    "Hrimnor's Hymn",
    "Hyaon's Fury",
    "Ichimonji",
    "Infractem",
    "Innsbury Edge",
    "Iron Commander",
    "Izaro's Dilemma",
    "Jack, the Axe",
    "Jorrhast's Blacksteel",
    "Kaom's Primacy",
    "Kingmaker",
    "Kitava's Feast",
    "Kondo's Pride",
    "Kongor's Undying Rage",
    "Lakishu's Blade",
    "Last Resort",
    "Lavianga's Wisdom",
    "Law of the Wilds",
    "Lifesprig",
    "Limbsplit",
    "Lioneye's Glare",
    "Maata's Teaching",
    "Mark of the Doubting Knight",
    "Marohi Erqi",
    "Martyr of Innocence",
    "Midnight Bargain",
    "Mightflay",
    "Mirebough",
    "Mjölner",
    "Mon'tregul's Grasp",
    "Moonbender's Wing",
    "Moonsorrow",
    "Mortem Morsu",
    "Nametaker",
    "Nebulis",
    "Nebuloch",
    "Ngamahu's Flame",
    "Null's Inclination",
    "Nuro's Harp",
    "Nycta's Lantern",
    "Obliteration",
    "Obliteration",
    "Oni-Goroshi",
    "Ornament of the East",
    "Oro's Sacrifice",
    "Panquetzaliztli",
    "Paradoxica",
    "Pillar of the Caged God",
    "Pillar of the Caged God",
    "Piscator's Vigil",
    "Piscator's Vigil",
    "Pledge of Hands",
    "Prismatic Eclipse",
    "Quecholli",
    "Queen's Decree",
    "Queen's Escape",
    "Quill Rain",
    "Rakiata's Dance",
    "Razor of the Seventh Sun",
    "Reach of the Council",
    "Realm Ender",
    "Realmshaper",
    "Reaper's Pursuit",
    "Rebuke of the Vaal",
    "Redbeak",
    "Reefbane",
    "Relentless Fury",
    "Relic of the Cycle",
    "Relic of the Pact",
    "Relic of the Pact",
    "Replica Advancing Fortress",
    "Replica Allure",
    "Replica Bitterdream",
    "Replica Bloodplay",
    "Replica Blood Thorn",
    "Replica Cold Iron Point",
    "Replica Dreamfeather",
    "Replica Duskdawn",
    "Replica Earendel's Embrace",
    "Replica Fencoil",
    "Replica Frostbreath",
    "Replica Harvest",
    "Replica Heartbreaker",
    "Replica Infractem",
    "Replica Innsbury Edge",
    "Replica Iron Commander",
    "Replica Kongor's Undying Rage",
    "Replica Last Resort",
    "Replica Midnight Bargain",
    "Replica Nebulis",
    "Replica Oro's Sacrifice",
    "Replica Paradoxica",
    "Replica Quill Rain",
    "Replica Soul Taker",
    "Replica Tempestuous Steel",
    "Replica Trypanon",
    "Replica Tulfall",
    "Replica Tulfall",
    "Replica Twyzel",
    "Replica Ungil's Gauche",
    "Replica Windripper",
    "Replica Wings of Entropy",
    "Reverberation Rod",
    "Rigwald's Charge",
    "Rigwald's Command",
    "Rigwald's Savagery",
    "Rive",
    "Roth's Reach",
    "Rust of Winter",
    "Sanguine Gambol",
    "Scaeva",
    "Scar of Fate",
    "Serle's Masterwork",
    "Severed in Sleep",
    "Shade of Solaris",
    "Shimmeron",
    "Shiversting",
    "Sign of the Sin Eater",
    "Silverbough",
    "Silverbranch",
    "Singularity",
    "Sinvicta's Mettle",
    "Sire of Shards",
    "Slivertongue",
    "Song of the Sirens",
    "Soul Taker",
    "Soulwrest",
    "Spine of the First Claimant",
    "Splinter of the Moon",
    "Starforge",
    "Storm Cloud",
    "Storm Prison",
    "Storm Prison",
    "Story of the Vaal",
    "Story of the Vaal",
    "Taproot",
    "Taryn's Shiver",
    "Tawhoa's Felling",
    "Terminus Est",
    "The Annihilating Light",
    "The Black Cane",
    "The Blood Reaper",
    "The Blood Thorn",
    "The Burden of Shadows",
    "The Cauteriser",
    "The Consuming Dark",
    "The Crimson Storm",
    "The Dancing Dervish",
    "The Dancing Duo",
    "The Dark Seer",
    "The Enmity Divine",
    "The Fulcrum",
    "The Geomantic Gyre",
    "The Gluttonous Tide",
    "The Goddess Bound",
    "The Goddess Scorned",
    "The Goddess Unleashed",
    "The Grey Spire",
    "The Gryphon",
    "The Harvest",
    "The Hidden Blade",
    "The Iron Mass",
    "The Living Blade",
    "The Poet's Pen",
    "The Princess",
    "The Redblade",
    "The Rippling Thoughts",
    "The Saviour",
    "The Scourge",
    "The Screaming Eagle",
    "The Searing Touch",
    "The Searing Touch",
    "The Stormheart",
    "The Stormwall",
    "The Supreme Truth",
    "The Surging Thoughts",
    "The Tempest",
    "The Tempestuous Steel",
    "The Wasp Nest",
    "The Whispering Ice",
    "The Winds of Fate",
    "The Yielding Mortality",
    "Thunder of the Dawn",
    "Tidebreaker",
    "Tipua Kaikohuru",
    "Touch of Anguish",
    "Tremor Rod",
    "Trypanon",
    "Tulborn",
    "Tulborn",
    "Tulfall",
    "Tulfall",
    "Twyzel",
    "Ungil's Gauche",
    "United in Dream",
    "Uul-Netol's Embrace",
    "Uul-Netol's Kiss",
    "Uul-Netol's Kiss",
    "Varunastra",
    "Vestige of Divinity",
    "Void Battery",
    "Voidforge",
    "Voidhome",
    "Voltaxic Rift",
    "Vulconus",
    "White Wind",
    "Wideswing",
    "Widowhail",
    "Widowmaker",
    "Wildslash",
    "Windripper",
    "Wings of Entropy",
    "Wings of Entropy",
    "Witchhunter's Judgment",
    "Xirgil's Crank",
    "Xoph's Inception",
    "Xoph's Inception",
    "Xoph's Nurture",
    "Yaomac's Accord",
    "Abberath's Hooves",
    "Abhorrent Interrogation",
    "Abyssus",
    "Admiral's Arrogance",
    "Aegis Aurora",
    "Ahn's Contempt",
    "Ahn's Heritage",
    "Ahuana's Bite",
    "Akoya's Gaze",
    "Alberon's Warpath",
    "Algor Mortis",
    "Allelopathy",
    "Allelopathy",
    "Alpha's Howl",
    "Ambu's Charge",
    "Ancient Skull",
    "Annihilation's Approach",
    "Apep's Slumber",
    "Apep's Slumber",
    "Apep's Supremacy",
    "Architect's Hand",
    "Architect's Hand",
    "Asenath's Chant",
    "Asenath's Gentle Touch",
    "Asenath's Mark",
    "Ashrend",
    "Asphyxia's Wrath",
    "Asphyxia's Wrath",
    "Assailum",
    "Atziri's Acuity",
    "Atziri's Mirror",
    "Atziri's Reflection",
    "Atziri's Splendour",
    "Atziri's Step",
    "Aukuna's Will",
    "Aurseize",
    "Beacon of Madness",
    "Belly of the Beast",
    "Bitterbind Point",
    "Blackgleam",
    "Blackgleam",
    "Blackgleam",
    "Black Sun Crest",
    "Black Zenith",
    "Blasphemer's Grasp",
    "Bloodbond",
    "Blood Price",
    "Blunderbore",
    "Bones of Ullr",
    "Bramblejack",
    "Breathstealer",
    "Brinerot Flag",
    "Brinerot Whalers",
    "Briskwrap",
    "Briskwrap",
    "Broadstroke",
    "Broken Faith",
    "Bronn's Lithe",
    "Bubonic Trail",
    "Cadigan's Crown",
    "Carcass Jack",
    "Ceaseless Feast",
    "Chains of Command",
    "Chalice of Horrors",
    "Chernobog's Pillar",
    "Cherrubim's Maleficence",
    "Chitus' Apex",
    "Cloak of Defiance",
    "Cloak of Flame",
    "Cloak of Tawm'r Isley",
    "Command of the Pit",
    "Corpsewalker",
    "Cospri's Will",
    "Cowl of the Ceraunophile",
    "Cowl of the Cryophile",
    "Cowl of the Thermophile",
    "Cragfall",
    "Craghead",
    "Craiceann's Carapace",
    "Craiceann's Chitin",
    "Craiceann's Pincers",
    "Craiceann's Tracks",
    "Crest of Desire",
    "Crest of Perandus",
    "Crown of Eyes",
    "Crown of the Inward Eye",
    "Crown of the Pale King",
    "Crown of the Tyrant",
    "Crown of Thorns",
    "Crystal Vault",
    "Curtain Call",
    "Dance of the Offered",
    "Dance of the Offered",
    "Daresso's Courage",
    "Daresso's Defiance",
    "Darkray Vectors",
    "Dawnbreaker",
    "Dawnstrider",
    "Death's Door",
    "Death's Oath",
    "Deerstalker",
    "Deidbell",
    "Deidbellow",
    "Demigod's Beacon",
    "Demigod's Dominance",
    "Demigod's Immortality",
    "Demigod's Stride",
    "Demigod's Touch",
    "Demigod's Triumph",
    "Demon Stitcher",
    "Dendrobate",
    "Deshret's Vise",
    "Devoto's Devotion",
    "Dialla's Malefaction",
    "Doedre's Malevolence",
    "Doedre's Scorn",
    "Doedre's Skin",
    "Doedre's Tenure",
    "Doppelgänger Guise",
    "Doryani's Delusion",
    "Doryani's Delusion",
    "Doryani's Delusion",
    "Doryani's Fist",
    "Doryani's Prototype",
    "Drillneck",
    "Duskblight",
    "Duskblight",
    "Dusktoe",
    "Dusktoe",
    "Eber's Unification",
    "Echoes of Creation",
    "El'Abin's Visage",
    "Elevore",
    "Emperor's Vigilance",
    "Empire's Grasp",
    "Entropic Devastation",
    "Esh's Mirror",
    "Esh's Mirror",
    "Esh's Visage",
    "Expedition's End",
    "Eye of Malice",
    "Ezomyte Hold",
    "Ezomyte Peak",
    "Facebreaker",
    "Fairgraves' Tricorne",
    "Faithguard",
    "Farrul's Bite",
    "Farrul's Chase",
    "Farrul's Fur",
    "Farrul's Pounce",
    "Fenumus' Shroud",
    "Fenumus' Spinnerets",
    "Fenumus' Toxins",
    "Fenumus' Weave",
    "Flamesight",
    "Flesh and Spirit",
    "Fleshcrafter",
    "Font of Thunder",
    "Forbidden Shako",
    "Fox's Fortune",
    "Foxshade",
    "Fractal Thoughts",
    "Frostferno",
    "Galesight",
    "Gamblesprint",
    "Gang's Momentum",
    "Garb of the Ephemeral",
    "Garukhan's Flight",
    "Geofri's Crest",
    "Geofri's Legacy",
    "Geofri's Sanctuary",
    "Ghostwrithe",
    "Giantsbane",
    "Glimpse of Chaos",
    "Glitterdisc",
    "Goldrim"
};

const QStringList SearchFilters::s_corpse_types = {
    "Any",
    "Eldritch",
    "Demon",
    "Construct",
    "Undead",
    "Beast",
    "Humanoid"
};

const QStringList SearchFilters::s_foil_variations = {
    "Any",
    "None",
    "Rainbow (Default)",
    "Any Voidborn Variant",
    "Amethyst",
    "Verdant",
    "Ruby",
    "Cobalt",
    "Sunset",
    "Aureate",
    "Any Celestial Variant",
    "Celestial Quartz",
    "Celestial Ruby",
    "Celestial Emerald",
    "Celestial Aureate",
    "Celestial Pearl",
    "Celestial Amethyst",
};

RequirementFilters::RequirementFilters(ProxyModel& model, QObject* parent)
    : QObject(parent)
{
    using Filter = SearchFilters::Filter;

    m_level_min = new MinFilter(Filter::LevelMin, model, &ItemInfo::requiredLevel, parent);
    m_level_max = new MaxFilter(Filter::LevelMax, model, &ItemInfo::requiredLevel, parent);

    m_strength_min = new MinFilter(Filter::LevelMin, model, &ItemInfo::requiredStrength, parent);
    m_strength_max = new MaxFilter(Filter::LevelMax, model, &ItemInfo::requiredStrength, parent);

    m_dexterity_min = new MinFilter(Filter::LevelMin, model, &ItemInfo::requiredStrength, parent);
    m_dexterity_max = new MaxFilter(Filter::LevelMax, model, &ItemInfo::requiredStrength, parent);

    m_intelligence_min = new MinFilter(Filter::LevelMin, model, &ItemInfo::requiredIntelligence, parent);
    m_intelligence_max = new MaxFilter(Filter::LevelMax, model, &ItemInfo::requiredIntelligence, parent);

}

SearchFilters::SearchFilters(ProxyModel& model, QObject* parent)
    : QObject(parent)
{
    m_requirements = new RequirementFilters(model, parent);
};
