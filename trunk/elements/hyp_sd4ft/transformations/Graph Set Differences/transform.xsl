<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumnClustered</xsl:variable>
<xsl:variable name="GraphTitle">SD-4ft Graph - set differences</xsl:variable>
<xsl:variable name="LegendShow">false</xsl:variable>
<xsl:variable name="GraphWidth">1</xsl:variable>
<xsl:variable name="GraphHeight">0,75</xsl:variable>

	
	


	<xsl:template match="hyp_sd4ft"> 
	<xsl:variable name="id_base" select="@id" />

	
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{$id_base}_4ftgraph1">
				<categories id="{$id_base}categories1">
					<category title="Ant &amp; Suc" id="{$id_base}A_S" />
					<category title="Ant &amp; ¬Suc" id="{$id_base}A_nS" />
					<category title="¬Ant &amp; Suc" id="{$id_base}nA_S" />
					<category title="¬Ant &amp; ¬Suc" id="{$id_base}nA_nS" />
				</categories>
				<chart title="first set" id="{$id_base}set1">
					<value value="{@a}" id="{$id_base}value1_1"/>
					<value value="{@b}" id="{$id_base}value1_2"/>
					<value value="{@c}" id="{$id_base}value1_3"/>
					<value value="{@d}" id="{$id_base}value1_4"/>
				</chart>			
				<chart title="second set" id="{$id_base}set2">
					<value value="{@e}" id="{$id_base}value2_1"/>
					<value value="{@f}" id="{$id_base}value2_2"/>
					<value value="{@g}" id="{$id_base}value2_3"/>
					<value value="{@h}" id="{$id_base}value2_4"/>
				</chart>			
			</graph>
		</paragraph>
	

	</xsl:template>
      




</xsl:stylesheet>
