def infer_label(file_name):
    file_name = file_name
    if "boxing" in file_name:
        return Constants.BOXING_LABEL
    if "running" in file_name:
        return Constants.RUNNING_LABEL
    if "jogging" in file_name:
        return Constants.JOGGING_LABEL
    if "walking" in file_name:
        return Constants.WALKING_LABEL
    if "handclapping" in file_name:
        return Constants.HANDCLAPPING_LABEL
    if "handwaving" in file_name:
        return Constants.HANDWAVING_LABEL
    if "bend" in file_name:
        return Constants.BEND_LABEL
    if "jack" in file_name:
        return Constants.JACK_LABEL
    # it is important that this check comes before the 'jump' one
    if "pjump" in file_name:
        return Constants.PJUMP_LABEL
    if "jump" in file_name:
        return Constants.JUMP_LABEL
    if "run" in file_name:
        return Constants.WEISSMAN_RUN_LABEL
    if "side" in file_name:
        return Constants.SIDE_LABEL
    if "skip" in file_name:
        return Constants.SKIP_LABEL
    if "walk" in file_name:
        return Constants.WEISSMAN_WALK_LABEL
    if "wave" in file_name:
        return Constants.WEISSMAN_WAVE_LABEL
    return -1