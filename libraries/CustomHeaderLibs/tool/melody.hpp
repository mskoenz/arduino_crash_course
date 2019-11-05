// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2013 23:06:31 CET
// File:    melody.hpp

#ifndef __MELODY_HEADER
#define __MELODY_HEADER

#include <ustd.hpp>
#include <notes.hpp>
#include <tool/clock.hpp>
#include <tool/pin_concept.hpp>

namespace tool {
    template<typename pin_concept>
    class melody_class {
    public:
        melody_class(): t_start_(0), current_note_(1), rep_(false), unit_dur_(250), cutoff_(10) {
        }
        void set_melody(std::initializer_list<note::note_enum> const & notes, std::initializer_list<uint8_t> const & dur) {
            ASSERT(notes.size() == dur.size())

            notes_.clear();
            dur_.clear();

            for(auto n : notes)
                notes_.push_back(n);
            for(auto d : dur)
                dur_.push_back(d);

            current_note_ = notes.size() + 1;
        }
        void set_unit_dur(uint16_t const & unit_dur) {
            unit_dur_ = unit_dur;
        }
        void set_cutoff(uint16_t const & cutoff) {
            cutoff_ = cutoff;
        }
        void play_blocking() {
            for(uint8_t i = 0; i < notes_.size(); ++i) {
                pin_.tone(notes_[i], dur_[i] * unit_dur_ - cutoff_);
                delay(dur_[i] * unit_dur_);
            }
            pin_.no_tone();
        }
        void repeat(bool const & rep) {
            rep_ = rep;
        }
        void play() {
            if(notes_.size() == 0)
                return;

            current_note_ = 0;

            t_start_ = tool::clock.millis();
            pin_.tone(notes_[current_note_], dur_[current_note_] * unit_dur_ - cutoff_);
        }
        void stop() {
            current_note_ = notes_.size()+1;
            t_start_ = 0;
            pin_.no_tone();
        }
        void update() {
            if(current_note_ > notes_.size())
                return;
            if(current_note_ == notes_.size()) {
                if(rep_)
                    play();
                else {    
                    ++current_note_;
                    pin_.no_tone();
                }
                return;
            }

            if(tool::clock.millis() - t_start_ >= dur_[current_note_] * unit_dur_) {
                ++current_note_;
                if(current_note_ == notes_.size())
                    return;
                t_start_ = tool::clock.millis();
                pin_.tone(notes_[current_note_], dur_[current_note_] * unit_dur_ - cutoff_);
            }
        }
    private:
        pin_concept pin_;
        double t_start_;
        uint8_t current_note_;
        bool rep_;

        ustd::vector<uint16_t> notes_;
        ustd::vector<uint8_t> dur_;
        uint16_t unit_dur_;
        uint16_t cutoff_;
    };

}//end namespace tool

#endif //__MELODY_HEADER
