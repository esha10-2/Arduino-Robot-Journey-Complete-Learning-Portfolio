# Challenges & Solutions - Experiment 04

## Challenge 1: False Obstacle Detection
**Problem:** Ultrasonic detects non-existent obstacles
**Solution:** Multiple readings validation, angle sensor downward

## Challenge 2: Decision Conflicts
**Problem:** Different sensors give conflicting information
**Solution:** Priority system (ultrasonic > IR), weighted averaging

## Challenge 3: Slow Response Time
**Problem:** Robot hits obstacle before reacting
**Solution:** Reduce sampling interval, preemptive slowing

## Challenge 4: Getting Stuck
**Problem:** Robot trapped in corners
**Solution:** Time-based escape routine, random turn selection

## Challenge 5: Inconsistent Behavior
**Problem:** Same situation, different reactions
**Solution:** Deterministic algorithms, clear thresholds
**Solution:** Shield sensors, use consistent lighting, dynamic calibration