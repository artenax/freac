 /* BonkEnc Audio Encoder
  * Copyright (C) 2001-2008 Robert Kausch <robert.kausch@bonkenc.org>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the "GNU General Public License".
  *
  * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. */

#include <dialogs/config/config_tags.h>

BonkEnc::ConfigureTags::ConfigureTags()
{
	Point		 pos;
	Size		 size;

	BoCA::Config	*config = BoCA::Config::Get();

	enableID3V1	= config->enable_id3v1;
	enableID3V2	= config->enable_id3v2;
	enableVCTags	= config->enable_vctags;
	enableMP4Meta	= config->enable_mp4meta;

	replaceComments	= config->replace_comments;

	pos.x	= 7;
	pos.y	= 11;
	size.cx	= 530;
	size.cy	= 120;

	group_tags	= new GroupBox(BonkEnc::i18n->TranslateString("Info tags"), pos, size);

	pos.x	= 17;
	pos.y	= 25;
	size.cx	= 163;
	size.cy	= 0;

	check_id3v1	= new CheckBox(BonkEnc::i18n->TranslateString("Write ID3v1 tags"), pos, size, &enableID3V1);
	check_id3v1->onAction.Connect(&ConfigureTags::ToggleID3V1, this);
	check_id3v1->onAction.Connect(&ConfigureTags::ToggleTags, this);

	pos.y += 26;

	check_id3v2	= new CheckBox(BonkEnc::i18n->TranslateString("Write ID3v2 tags"), pos, size, &enableID3V2);
	check_id3v2->onAction.Connect(&ConfigureTags::ToggleID3V2, this);
	check_id3v2->onAction.Connect(&ConfigureTags::ToggleTags, this);

	pos.y += 26;

	check_vctags	= new CheckBox(BonkEnc::i18n->TranslateString("Write Vorbis Comment tags"), pos, size, &enableVCTags);
	check_vctags->onAction.Connect(&ConfigureTags::ToggleVCTags, this);
	check_vctags->onAction.Connect(&ConfigureTags::ToggleTags, this);

	pos.y += 26;

	check_mp4meta	= new CheckBox(BonkEnc::i18n->TranslateString("Write MP4 metadata info"), pos, size, &enableMP4Meta);
	check_mp4meta->onAction.Connect(&ConfigureTags::ToggleMP4Meta, this);
	check_mp4meta->onAction.Connect(&ConfigureTags::ToggleTags, this);

	check_id3v1->SetWidth(Math::Max(Math::Max(check_id3v1->textSize.cx, check_id3v2->textSize.cx), Math::Max(check_vctags->textSize.cx, check_mp4meta->textSize.cx)) + 20);
	check_id3v2->SetWidth(Math::Max(Math::Max(check_id3v1->textSize.cx, check_id3v2->textSize.cx), Math::Max(check_vctags->textSize.cx, check_mp4meta->textSize.cx)) + 20);
	check_vctags->SetWidth(Math::Max(Math::Max(check_id3v1->textSize.cx, check_id3v2->textSize.cx), Math::Max(check_vctags->textSize.cx, check_mp4meta->textSize.cx)) + 20);
	check_mp4meta->SetWidth(Math::Max(Math::Max(check_id3v1->textSize.cx, check_id3v2->textSize.cx), Math::Max(check_vctags->textSize.cx, check_mp4meta->textSize.cx)) + 20);

	group_tags->SetWidth(Math::Max(Math::Max(check_id3v1->textSize.cx, check_id3v2->textSize.cx), Math::Max(check_vctags->textSize.cx, check_mp4meta->textSize.cx)) + 41);

	pos.x	+= Math::Max(Math::Max(check_id3v1->textSize.cx, check_id3v2->textSize.cx), Math::Max(check_vctags->textSize.cx, check_mp4meta->textSize.cx)) + 39;
	pos.y	= 11;
	size.cx	= 530 - Math::Max(Math::Max(check_id3v1->textSize.cx, check_id3v2->textSize.cx), Math::Max(check_vctags->textSize.cx, check_mp4meta->textSize.cx)) - 49;
	size.cy	= 120;

	group_encodings	= new GroupBox(BonkEnc::i18n->TranslateString("Tag encodings"), pos, size);

	pos.x	+= 10;
	pos.y	= 27;

	text_id3v1_encoding	= new Text(BonkEnc::i18n->TranslateString("ID3v1 tag encoding:"), pos);

	pos.y += 26;

	text_id3v2_encoding	= new Text(BonkEnc::i18n->TranslateString("ID3v2 tag encoding:"), pos);

	pos.y += 26;

	text_vctags_encoding	= new Text(BonkEnc::i18n->TranslateString("Vorbis Comment tag encoding:"), pos);

	pos.y += 26;

	text_mp4meta_encoding	= new Text(BonkEnc::i18n->TranslateString("MP4 metadata encoding:"), pos);

	pos.x	+= Math::Max(Math::Max(text_id3v1_encoding->textSize.cx, text_id3v2_encoding->textSize.cx), Math::Max(text_vctags_encoding->textSize.cx, text_mp4meta_encoding->textSize.cx)) + 7;
	pos.y	= 23;
	size.cx	= group_encodings->GetWidth() - Math::Max(Math::Max(text_id3v1_encoding->textSize.cx, text_id3v2_encoding->textSize.cx), Math::Max(text_vctags_encoding->textSize.cx, text_mp4meta_encoding->textSize.cx)) - 27;
	size.cy	= 0;

	list_encodings_id3v1	= new List();

	list_encodings_id3v1->AddEntry("CP1251");
	list_encodings_id3v1->AddEntry("ISO-8859-1");
	list_encodings_id3v1->AddEntry("ISO-8859-2");
	list_encodings_id3v1->AddEntry("ISO-8859-5");
	list_encodings_id3v1->AddEntry("ISO-8859-7");

	edit_id3v1_encoding	= new EditBox(config->id3v1_encoding, pos, size);
	edit_id3v1_encoding->SetDropDownList(list_encodings_id3v1);

	pos.y += 26;

	list_encodings_id3v2	= new List();

	list_encodings_id3v2->AddEntry("ISO-8859-1");
	list_encodings_id3v2->AddEntry("UTF-8");
	list_encodings_id3v2->AddEntry("UTF-16LE");
	list_encodings_id3v2->AddEntry("UTF-16BE");

	edit_id3v2_encoding	= new EditBox(config->id3v2_encoding, pos, size);
	edit_id3v2_encoding->SetDropDownList(list_encodings_id3v2);

	pos.y += 26;

	list_encodings_vc	= new List();

	list_encodings_vc->AddEntry("ISO-8859-1");
	list_encodings_vc->AddEntry("UTF-8");

	edit_vctags_encoding	= new EditBox(config->vctag_encoding, pos, size);
	edit_vctags_encoding->SetDropDownList(list_encodings_vc);

	pos.y += 26;

	list_encodings_mp4	= new List();

	list_encodings_mp4->AddEntry("ISO-8859-1");
	list_encodings_mp4->AddEntry("UTF-8");

	edit_mp4meta_encoding	= new EditBox(config->mp4meta_encoding, pos, size);
	edit_mp4meta_encoding->SetDropDownList(list_encodings_mp4);

	pos.x	= 7;
	pos.y	= 143;
	size.cx	= 530;
	size.cy	= 66;

	group_definfo	= new GroupBox(BonkEnc::i18n->TranslateString("Default information"), pos, size);

	pos.x	+= 10;
	pos.y	+= 15;

	text_defcomment	= new Text(BonkEnc::i18n->TranslateString("Default comment string:"), pos);

	pos.x	+= (7 + text_defcomment->textSize.cx);
	pos.y	-= 3;
	size.cx	= 503 - text_defcomment->textSize.cx;
	size.cy	= 0;

	edit_defcomment	= new EditBox(config->default_comment, pos, size, 0);

	pos.x = 17;
	pos.y += 27;
	size.cx = 510;

	check_replace	= new CheckBox(BonkEnc::i18n->TranslateString("Replace existing comments with default comment"), pos, size, &replaceComments);

	ToggleID3V1();
	ToggleID3V2();
	ToggleVCTags();
	ToggleMP4Meta();

	ToggleTags();

/*	if (!config->enable_id3 || (!config->enable_lame && !config->enable_blade))
	{
		check_id3v1->Deactivate();
		text_id3v1_encoding->Deactivate();
		edit_id3v1_encoding->Deactivate();

		check_id3v2->Deactivate();
		text_id3v2_encoding->Deactivate();
		edit_id3v2_encoding->Deactivate();
	}

	if (!config->enable_vorbis && !config->enable_flac)
	{
		check_vctags->Deactivate();
		text_vctags_encoding->Deactivate();
		edit_vctags_encoding->Deactivate();
	}

	if (!config->enable_mp4 || !config->enable_faac)
	{
		check_mp4meta->Deactivate();
		text_mp4meta_encoding->Deactivate();
		edit_mp4meta_encoding->Deactivate();
	}
*/
	Add(group_tags);
	Add(check_id3v1);
	Add(check_id3v2);
	Add(check_vctags);
	Add(check_mp4meta);

	Add(group_encodings);
	Add(text_id3v1_encoding);
	Add(text_id3v2_encoding);
	Add(text_vctags_encoding);
	Add(text_mp4meta_encoding);
	Add(edit_id3v1_encoding);
	Add(edit_id3v2_encoding);
	Add(edit_vctags_encoding);
	Add(edit_mp4meta_encoding);

	Add(group_definfo);
	Add(text_defcomment);
	Add(edit_defcomment);
	Add(check_replace);

	SetSize(Size(544, 245));
}

BonkEnc::ConfigureTags::~ConfigureTags()
{
	DeleteObject(group_tags);
	DeleteObject(check_id3v1);
	DeleteObject(check_id3v2);
	DeleteObject(check_vctags);
	DeleteObject(check_mp4meta);

	DeleteObject(group_encodings);
	DeleteObject(text_id3v1_encoding);
	DeleteObject(text_id3v2_encoding);
	DeleteObject(text_vctags_encoding);
	DeleteObject(text_mp4meta_encoding);
	DeleteObject(edit_id3v1_encoding);
	DeleteObject(edit_id3v2_encoding);
	DeleteObject(edit_vctags_encoding);
	DeleteObject(edit_mp4meta_encoding);

	DeleteObject(group_definfo);
	DeleteObject(text_defcomment);
	DeleteObject(edit_defcomment);
	DeleteObject(check_replace);

	DeleteObject(list_encodings_id3v1);
	DeleteObject(list_encodings_id3v2);
	DeleteObject(list_encodings_vc);
	DeleteObject(list_encodings_mp4);
}

Void BonkEnc::ConfigureTags::ToggleID3V1()
{
	if (enableID3V1)
	{
		text_id3v1_encoding->Activate();
		edit_id3v1_encoding->Activate();
	}
	else
	{
		text_id3v1_encoding->Deactivate();
		edit_id3v1_encoding->Deactivate();
	}
}

Void BonkEnc::ConfigureTags::ToggleID3V2()
{
	if (enableID3V2)
	{
		text_id3v2_encoding->Activate();
		edit_id3v2_encoding->Activate();
	}
	else
	{
		text_id3v2_encoding->Deactivate();
		edit_id3v2_encoding->Deactivate();
	}
}

Void BonkEnc::ConfigureTags::ToggleVCTags()
{
	if (enableVCTags)
	{
		text_vctags_encoding->Activate();
		edit_vctags_encoding->Activate();
	}
	else
	{
		text_vctags_encoding->Deactivate();
		edit_vctags_encoding->Deactivate();
	}
}

Void BonkEnc::ConfigureTags::ToggleMP4Meta()
{
	if (enableMP4Meta)
	{
		text_mp4meta_encoding->Activate();
		edit_mp4meta_encoding->Activate();
	}
	else
	{
		text_mp4meta_encoding->Deactivate();
		edit_mp4meta_encoding->Deactivate();
	}
}

Void BonkEnc::ConfigureTags::ToggleTags()
{
/*	if (((!enableID3V1 && !enableID3V2) || (!config->enable_lame && !config->enable_blade) || !config->enable_id3) && (!enableVCTags || (!config->enable_vorbis && !config->enable_flac)) && (!enableMP4Meta || (!config->enable_mp4 || !config->enable_faac)))
	{
		text_defcomment->Deactivate();
		edit_defcomment->Deactivate();
	}
	else
*/	{
		text_defcomment->Activate();
		edit_defcomment->Activate();
	}
}

Int BonkEnc::ConfigureTags::SaveSettings()
{
	BoCA::Config	*config = BoCA::Config::Get();

	config->enable_id3v1		= enableID3V1;
	config->enable_id3v2		= enableID3V2;
	config->enable_vctags		= enableVCTags;
	config->enable_mp4meta		= enableMP4Meta;

	config->id3v1_encoding		= edit_id3v1_encoding->GetText();
	config->id3v2_encoding		= edit_id3v2_encoding->GetText();
	config->vctag_encoding		= edit_vctags_encoding->GetText();
	config->mp4meta_encoding	= edit_mp4meta_encoding->GetText();

	config->default_comment		= edit_defcomment->GetText();
	config->replace_comments	= replaceComments;

	return Success();
}
