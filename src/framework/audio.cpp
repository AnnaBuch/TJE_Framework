//#include "audio.h"
//
//std::map<std::string, audio*> audio::saudiosloaded;
//
//audio::audio()
//{
//	sample = 0;
//}
//
//audio::~audio()
//{
//	bass_samplefree(sample);
//}
//
//// use "bass_sample_loop" in flags to play audio as a loop
//bool audio::load(const std::string& filename, uint8_t flags)
//{
//	sample = bass_sampleload(
//		false,  				// from internal memory
//		filename.c_str(),		// filepath
//		0,						// offset
//		0,						// length
//		3,						// max playbacks
//		flags					// flags
//	);
//
//	return sample != 0;
//}
//
//hchannel audio::play(float volume)
//{
//	// store sample channel in handler
//	hchannel channel = bass_samplegetchannel(sample, false);
//
//	// change channel volume
//	bass_channelsetattribute(channel, bass_attrib_vol, volume);
//
//	// play channel
//	bass_channelplay(channel, true);
//
//	return channel;
//}
//
//bool audio::init()
//{
//	if (bass_init(-1, 44100, 0, 0, null) == false) {
//		// error with sound device
//		return false;
//	}
//
//	return true;
//}
//
//void audio::destroy()
//{
//	bass_free();
//}
//
//audio* audio::get(const std::string& filename, uint8_t flags)
//{
//	std::map<std::string, audio*>::iterator it = saudiosloaded.find(filename);
//	if (it != saudiosloaded.end())
//		return it->second;
//
//	audio* audio = new audio();
//	if (!audio->load(filename, flags))
//		return nullptr;
//
//	saudiosloaded[filename] = audio;
//
//	return audio;
//}
//
//hchannel audio::play(const std::string& filename, float volume, uint8_t flags)
//{
//	audio* audio = audio::get(filename, flags);
//
//	if (!audio) {
//		return 0;
//	}
//
//	return audio->play(volume);
//}
//
//// make sure the sample has been loaded using "bass_sample_3d" flag
//hchannel audio::play3d(const std::string& filename, vector3 pos, float volume)
//{
//	audio* audio = audio::get(filename, bass_sample_3d);
//
//	if (!audio) {
//		return 0;
//	}
//
//	hchannel channel = audio->play(volume);
//
//	// set audio position in space
//	bass_3dvector bass_position = { pos.x, pos.y, pos.z };
//	bass_channelset3dposition(channel, &bass_position, null, null);
//
//	// apply changes to 3d system
//	bass_apply3d();
//
//	return channel;
//}
//
//bool audio::stop(hchannel channel)
//{
//	return bass_channelstop(channel);
//}