scene_id: 7CB350B4-023A-49EA-8F90-CC14789278B4
scene_name: MyScene
child:
  - name: Floor
    enabled: true
    id: 12353103114721021476
    component:
      - name: Transform
        enabled: true
        id: 10452791160716319910
        type: 1
        data:
          position:
            x: -144.907837
            y: 2.02149105
            z: 145.491409
          rotation:
            x: 0
            y: 0
            z: 0
            w: 1
          scale:
            x: 0.061598815
            y: 0.061598815
            z: 0.061598815
      - name: Mesh
        enabled: true
        id: 11485068470481755150
        type: 4
        data:
          model_path: ./assets/models/Floor.fbx
          mesh:
            - enabled: true
              texture_file_name: PlayerDiffuse
              texture_type: 0
            - enabled: true
              texture_file_name: PlanksDiffuse
              texture_type: 0
            - enabled: true
              texture_file_name: PlanksDiffuse
              texture_type: 0
  - name: Player
    enabled: true
    id: 3455403891046494354
    component:
      - name: Transform
        enabled: true
        id: 15901742237047788000
        type: 1
        data:
          position:
            x: 9.53301048
            y: 2.1610651
            z: 31.0210171
          rotation:
            x: 0
            y: -0.164679527
            z: 0
            w: 0.986347198
          scale:
            x: 0.187199995
            y: 0.187199995
            z: 0.187199995
      - name: Mesh
        enabled: true
        id: 14817143812054290503
        type: 4
        data:
          model_path: ./assets/models/Player.fbx
          mesh:
            - enabled: true
              texture_file_name: GunDiffuse
              texture_type: 0
            - enabled: true
              texture_file_name: PlayerDiffuse
              texture_type: 0
  - name: Dollhouse
    enabled: true
    id: 14253224874114533032
    component:
      - name: Transform
        enabled: true
        id: 9376485718642429271
        type: 1
        data:
          position:
            x: -77.2852173
            y: 2.45454597
            z: -116.297119
          rotation:
            x: 0
            y: 0.998045266
            z: 0
            w: 0.0624951907
          scale:
            x: 0.125580043
            y: 0.125580028
            z: 0.125580043
      - name: Mesh
        enabled: true
        id: 18154537803902444557
        type: 4
        data:
          model_path: ./assets/models/Dollhouse.fbx
          mesh:
            - enabled: true
              texture_file_name: DollhouseDiffuse
              texture_type: 0
  - name: Drawers
    enabled: true
    id: 3618530690104612962
    component:
      - name: Transform
        enabled: true
        id: 18306577094962255835
        type: 1
        data:
          position:
            x: 115.273911
            y: 2.02263832
            z: -86.5007706
          rotation:
            x: 0
            y: 0.849097967
            z: 0
            w: 0.528235376
          scale:
            x: 0.0474692434
            y: 0.0474692285
            z: 0.0474692434
      - name: Mesh
        enabled: true
        id: 7776015979845377633
        type: 4
        data:
          model_path: ./assets/models/Drawers.fbx
          mesh:
            - enabled: true
              texture_file_name: DrawersDiffuse
              texture_type: 0
  - name: Robot
    enabled: true
    id: 8545458865380190813
    component:
      - name: Transform
        enabled: true
        id: 10490108894767518975
        type: 1
        data:
          position:
            x: 89.3525848
            y: 3.93938446
            z: 46.7346001
          rotation:
            x: 0
            y: 0.994314849
            z: 0
            w: -0.106480211
          scale:
            x: 0.109200008
            y: 0.109199978
            z: 0.109200008
      - name: Mesh
        enabled: true
        id: 6038186604454664525
        type: 4
        data:
          model_path: ./assets/models/Robot.FBX
          mesh:
            - enabled: true
              texture_file_name: RobotDiffuse
              texture_type: 0
  - name: Wall
    enabled: true
    id: 3806548446174385471
    component:
      - name: Transform
        enabled: true
        id: 8237458402934936419
        type: 1
        data:
          position:
            x: 161.860855
            y: 0
            z: -162.078934
          rotation:
            x: 0
            y: 0.999993026
            z: 0
            w: 0.00373525755
          scale:
            x: 0.0633420199
            y: 0.0633420125
            z: 0.0633420199
      - name: Mesh
        enabled: true
        id: 11975958800148177208
        type: 4
        data:
          model_path: ./assets/models/Wall.FBX
          mesh:
            - enabled: true
              texture_file_name: WallDiffuse
              texture_type: 0
            - enabled: true
              texture_file_name: WallDiffuse
              texture_type: 0
  - name: Bunny
    enabled: true
    id: 12721570396058998999
    component:
      - name: Transform
        enabled: true
        id: 4271098022495898861
        type: 1
        data:
          position:
            x: 114.49115
            y: 66.8752365
            z: -99.9156418
          rotation:
            x: 0
            y: -0.367866904
            z: 0
            w: 0.929878473
          scale:
            x: 0.229080051
            y: 0.229080051
            z: 0.229080051
      - name: Mesh
        enabled: true
        id: 5151090163262804262
        type: 4
        data:
          model_path: ./assets/models/Zombunny.fbx
          mesh:
            - enabled: true
              texture_file_name: ZomBunnyDiffuse
              texture_type: 0
            - enabled: true
              texture_file_name: ZomBunnyDiffuse
              texture_type: 0